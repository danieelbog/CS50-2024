#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int grey_color_value = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = image[i][j].rgbtGreen = image[i][j].rgbtRed = grey_color_value;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int middle = round(width / 2.0);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < middle; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double sr = 0, sg = 0, sb = 0, count = 0;
            for (int row = -1; row <= 1; row++)
            {
                for (int col = -1; col <= 1; col++)
                {
                    if (i + row < 0 || i + row > height - 1)
                    {
                        continue;
                    }

                    if (j + col < 0 || j + col > width - 1)
                    {
                        continue;
                    }

                    count++;
                    sr += image[i + row][j + col].rgbtRed;
                    sg += image[i + row][j + col].rgbtGreen;
                    sb += image[i + row][j + col].rgbtBlue;
                }
            }

            temp[i][j].rgbtRed = round(sr / count);
            temp[i][j].rgbtGreen = round(sg / count);
            temp[i][j].rgbtBlue = round(sb / count);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int gx[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};

    int gy[9] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};

    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double srx = 0, sgx = 0, sbx = 0, sry = 0, sgy = 0, sby = 0;
            int count = -1;

            for (int row = -1; row <= 1; row++)
            {
                for (int col = -1; col <= 1; col++)
                {
                    count++;

                    if (i + row < 0 || i + row > height - 1)
                    {
                        continue;
                    }

                    if (j + col < 0 || j + col > width - 1)
                    {
                        continue;
                    }

                    srx += image[i + row][j + col].rgbtRed * gx[count];
                    sgx += image[i + row][j + col].rgbtGreen * gx[count];
                    sbx += image[i + row][j + col].rgbtBlue * gx[count];

                    sry += image[i + row][j + col].rgbtRed * gy[count];
                    sgy += image[i + row][j + col].rgbtGreen * gy[count];
                    sby += image[i + row][j + col].rgbtBlue * gy[count];
                }
            }

            temp[i][j].rgbtRed = round(sqrt(srx * srx + sry * sry) > 255 ? 255 : sqrt(srx * srx + sry * sry));
            temp[i][j].rgbtGreen = round(sqrt(sgx * sgx + sgy * sgy) > 255 ? 255 : sqrt(sgx * sgx + sgy * sgy));
            temp[i][j].rgbtBlue = round(sqrt(sbx * sbx + sby * sby) > 255 ? 255 : sqrt(sbx * sbx + sby * sby));
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }

    return;
}
