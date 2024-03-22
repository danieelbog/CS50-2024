-- Keep a log of any SQL queries you execute as you solve the mystery.
-- CREATE TABLE crime_scene_reports (
--     id INTEGER,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     street TEXT,
--     description TEXT,
--     PRIMARY KEY(id)
-- );
-- CREATE TABLE interviews (
--     id INTEGER,
--     name TEXT,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     transcript TEXT,
--     PRIMARY KEY(id)
-- );
-- CREATE TABLE atm_transactions (
--     id INTEGER,
--     account_number INTEGER,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     atm_location TEXT,
--     transaction_type TEXT,
--     amount INTEGER,
--     PRIMARY KEY(id)
-- );
-- CREATE TABLE bank_accounts (
--     account_number INTEGER,
--     person_id INTEGER,
--     creation_year INTEGER,
--     FOREIGN KEY(person_id) REFERENCES people(id)
-- );
-- CREATE TABLE airports (
--     id INTEGER,
--     abbreviation TEXT,
--     full_name TEXT,
--     city TEXT,
--     PRIMARY KEY(id)
-- );
-- CREATE TABLE flights (
--     id INTEGER,
--     origin_airport_id INTEGER,
--     destination_airport_id INTEGER,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     hour INTEGER,
--     minute INTEGER,
--     PRIMARY KEY(id),
--     FOREIGN KEY(origin_airport_id) REFERENCES airports(id),
--     FOREIGN KEY(destination_airport_id) REFERENCES airports(id)
-- );
-- CREATE TABLE passengers (
--     flight_id INTEGER,
--     passport_number INTEGER,
--     seat TEXT,
--     FOREIGN KEY(flight_id) REFERENCES flights(id)
-- );
-- CREATE TABLE phone_calls (
--     id INTEGER,
--     caller TEXT,
--     receiver TEXT,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     duration INTEGER,
--     PRIMARY KEY(id)
-- );
-- CREATE TABLE people (
--     id INTEGER,
--     name TEXT,
--     phone_number TEXT,
--     passport_number INTEGER,
--     license_plate TEXT,
--     PRIMARY KEY(id)
-- );
-- CREATE TABLE bakery_security_logs (
--     id INTEGER,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     hour INTEGER,
--     minute INTEGER,
--     activity TEXT,
--     license_plate TEXT,
--     PRIMARY KEY(id)
-- );



-- Check the crime reports
SELECT *
FROM crime_scene_reports
WHERE year = 2023
AND month = 7
AND day = 28;

-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
-- Interviews were conducted today with three witnesses who were present at the time –
-- each of their interview transcripts mentions the bakery.

-- Check interviews with the word bakery as mentioned in the report above
SELECT *
FROM interviews
WHERE year = 2023
AND month = 7
AND day = 28
AND transcript LIKE '%bakery%';

-- Interview 1 lead:
-- Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot
-- and drive away. If you have security footage from the bakery parking lot,
-- you might want to look for cars that left the parking lot in that time frame.

-- Check the security footage from exit in car from 10:15 to 10:25 at parking lot
SELECT DISTINCT p.name
FROM people p
JOIN bakery_security_logs bsl ON p.license_plate = bsl.license_plate
AND bsl.year = 2023
AND bsl.month = 7
AND bsl.day = 28
AND bsl.hour = 10
AND bsl.minute >= 15
AND bsl.minute <= 25
AND bsl.activity = 'exit'
ORDER BY p.name;

-- +---------+
-- |  name   |
-- +---------+
-- | Barry   |
-- | Bruce   |
-- | Diana   |
-- | Iman    |
-- | Kelsey  |
-- | Luca    |
-- | Sofia   |
-- | Vanessa |
-- +---------+

-- Interview 2 lead:
-- I don't know the thief's name, but it was someone I recognized.
-- Earlier this morning, before I arrived at Emma's bakery,
-- I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.

SELECT DISTINCT p.name
FROM people p
JOIN bank_accounts ba ON p.id = ba.person_id
JOIN atm_transactions atm ON ba.account_number = atm.account_number
AND atm.year = 2023
AND atm.month = 7
AND atm.day = 28
AND atm.atm_location = "Leggett Street"
AND atm.transaction_type = "withdraw"
ORDER BY p.name;

-- same people from past query
-- +---------+
-- |  name   |
-- +---------+
-- | Bruce   |
-- | Diana   |
-- | Iman    |
-- | Luca    |
-- +---------+

-- Interview 3 lead:
-- As the thief was leaving the bakery,
-- they called someone who talked to them for less than a minute.
-- In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
-- The thief then asked the person on the other end of the phone to purchase the flight ticket.

SELECT DISTINCT p.name
FROM people p
JOIN phone_calls pc ON p.phone_number = pc.caller
WHERE pc.year = 2023
AND pc.month = 7
AND pc.day = 28
AND pc.duration < 60
ORDER BY p.name;

-- same people from past query
-- +---------+
-- |  name   |
-- +---------+
-- | Bruce   |
-- | Diana   |
-- +---------+

SELECT f.id AS flight_id,
       f.hour,
       f.minute,
       pe.name AS passenger_name,
       f.destination_airport_id AS flight_destination
FROM flights f
JOIN passengers pa ON f.id = pa.flight_id
JOIN people pe ON pa.passport_number = pe.passport_number
JOIN airports a ON f.origin_airport_id = a.id
AND a.city = 'Fiftyville'
WHERE f.id = (
    SELECT id
    FROM flights
    WHERE year = 2023
    AND month = 7
    AND day = 29
    ORDER BY hour, minute
    LIMIT 1
)
ORDER BY f.hour, f.minute, pe.name;

-- +-----------+------+--------+----------------+--------------------+
-- | flight_id | hour | minute | passenger_name | flight_destination |
-- +-----------+------+--------+----------------+--------------------+
-- | 36        | 8    | 20     | Bruce          | 4                  |
-- | 36        | 8    | 20     | Doris          | 4                  |
-- | 36        | 8    | 20     | Edward         | 4                  |
-- | 36        | 8    | 20     | Kelsey         | 4                  |
-- | 36        | 8    | 20     | Kenny          | 4                  |
-- | 36        | 8    | 20     | Luca           | 4                  |
-- | 36        | 8    | 20     | Sofia          | 4                  |
-- | 36        | 8    | 20     | Taylor         | 4                  |
-- +-----------+------+--------+----------------+--------------------+
-- Since Diana isn't on this flight, BRUCE is the criminal!

-- Bruce is heading to:
SELECT *
FROM airports
WHERE id = 4;

-- +----+--------------+-------------------+---------------+
-- | id | abbreviation |     full_name     |     city      |
-- +----+--------------+-------------------+---------------+
-- | 4  | LGA          | LaGuardia Airport | New York City |
-- +----+--------------+-------------------+---------------+

-- Now we need to find who Bruce was talking to on the Phone

SELECT DISTINCT p.name
FROM people p
JOIN phone_calls pc ON p.phone_number = pc.receiver
WHERE pc.caller = '(367) 555-5533'
AND pc.year = 2023
AND pc.month = 7
AND pc.day = 28
AND pc.duration < 60
ORDER BY p.name;

-- +-------+
-- | name  |
-- +-------+
-- | Robin |
-- +-------+

-- Bruce called Robin, so Robin is the ACCOMPLICE!
