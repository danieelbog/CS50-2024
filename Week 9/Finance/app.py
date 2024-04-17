import os
from datetime import datetime

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    user = db.execute("SELECT * from users where id = ?", session["user_id"])
    cash = user[0]["cash"]
    total = cash

    portfolio = db.execute(
        "SELECT symbol, sum(quantity) as sumquantity, price from transactions WHERE user_id = ? GROUP BY symbol", session["user_id"])
    for share in portfolio:
        lookup_share = lookup(share["symbol"])
        share["price"] = lookup_share["price"]
        share["total"] = share["price"] * share["sumquantity"]
        total += share["total"]

    return render_template("index.html", portfolio=portfolio, cash=cash, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("symbol cannot be blank", 400)

        if not request.form.get("shares").isdigit():
            return apology("shares must be a number", 400)

        if not request.form.get("shares") or 0 > int(request.form.get("shares")):
            return apology("shares cannot be empty/negative", 400)

        symbol = lookup(request.form.get("symbol"))
        if not symbol:
            return apology("symbol not found", 400)

        price = symbol["price"]
        user = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        cash = user[0]["cash"]
        balance = float(cash) - float(request.form.get("shares")) * float(price)

        if balance < 0:
            return apology("not enough money")

        db.execute("UPDATE users SET cash = ? WHERE id = ?", balance, session["user_id"])

        # CREATE TABLE IF NOT EXISTS transactions (
        #     id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
        #     user_id INTEGER NOT NULL,
        #     symbol TEXT NOT NULL,
        #     quantity NUMERIC NOT NULL,
        #     price NUMERIC NOT NULL,
        #     create_date DATETIME NOT NULL,
        #     FOREIGN KEY (user_id) REFERENCES users(id)
        # )

        db.execute("INSERT INTO transactions (symbol, quantity, price, user_id, create_date) VALUES(?, ?, ?, ?, ?)",
                   symbol["symbol"], int(request.form.get("shares")), price, session["user_id"], datetime.now())

        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    transactions = db.execute(
        "SELECT symbol, price, quantity, create_date FROM transactions WHERE user_id = ?", session["user_id"])
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("must provide symbol", 400)

        quote = lookup(request.form.get("symbol"))
        if not quote:
            return apology("missing quote", 400)

        return render_template("quoted.html", quote=quote)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        if not request.form.get("username"):
            return apology("must provide username", 400)
        elif not request.form.get("password"):
            return apology("must provide password", 400)
        elif not request.form.get("confirmation"):
            return apology("must provide password confirmation", 400)
        elif request.form.get("confirmation") != request.form.get("password"):
            return apology("passwords don't match", 400)
        elif db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username")):
            return apology("user already exists", 400)

        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", request.form.get(
            "username"), generate_password_hash(request.form.get("password")))
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 400)

        session["user_id"] = rows[0]["id"]

        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("please select what to sell", 400)

        if not request.form.get("shares").isdigit():
            return apology("shares must be a number", 400)

        if not request.form.get("shares") or int(request.form.get("shares")) < 0:
            return apology("shares cannot be empty or negative", 400)

        currenct_symbol_transactions = db.execute("SELECT *, sum(quantity) as sumquantity FROM transactions WHERE user_id = ? AND symbol =  ? GROUP BY symbol",
                                                  session["user_id"], request.form.get("symbol"))

        if len(currenct_symbol_transactions) < 1:
            return apology("Symbol not found")

        if currenct_symbol_transactions[0]["sumquantity"] < int(request.form.get("shares")):
            return apology("not enough shares owned", 400)

        symbol = lookup(currenct_symbol_transactions[0]["symbol"])
        price = symbol["price"]
        balance = price * float(request.form.get("shares"))

        db.execute("UPDATE users SET cash = cash + ?", balance)
        db.execute("INSERT INTO transactions (symbol, quantity, price, user_id, create_date) VALUES(?, ?, ?, ?, ?)",
                   symbol["symbol"], -int(request.form.get("shares")), price, session["user_id"], datetime.now())

        return redirect("/")
    else:
        symbols = db.execute(
            "SELECT symbol FROM transactions WHERE user_id = ? GROUP BY symbol", session["user_id"])
        return render_template("sell.html", symbols=symbols)


@app.route("/password", methods=["GET", "POST"])
@login_required
def password():
    if request.method == "POST":
        if not request.form.get("currentPassword"):
            return apology("must provide your current password", 400)

        if not request.form.get("newPassword"):
            return apology("must provide new password", 400)

        if not request.form.get("confirmPassword"):
            return apology("must provide confirm password", 400)

        if request.form.get("newPassword") != request.form.get("confirmPassword"):
            return apology("new password and confirm password mismatch", 400)

        if request.form.get("newPassword") == request.form.get("currentPassword"):
            return apology("new password is too similar with the old password", 400)

        user = db.execute("SELECT * from users where id = ?", session["user_id"])
        if len(user) < 1:
            session.clear()
            return apology("current user not found", 400)

        if not check_password_hash(
            user[0]["hash"], request.form.get("currentPassword")
        ):
            return apology("current password mismatch", 400)

        newPassword = generate_password_hash(request.form.get("newPassword"))
        db.execute("UPDATE users SET hash = ? WHERE id = ?", newPassword, session["user_id"])

        return redirect("/")
    else:
        return render_template("password.html")
