# Weather Stats
This program gets the path of the RAWS weather file containing weather data formatted as follows (columns in order):
- Month (Integer)
- Day (Integer) 
- Precipitation – the daily rain amount specified in hundredths of an inch or millimeters (Integer)
- Hour 1 – the hour at which the minimum temperature was recorded (Integer: 0-2400) 
- Hour 2 – the hour at which the maximum temperature was recorded (Integer: 0-2400) 
- Temperature 1 – the minimum temperature in degrees Fahrenheit or Celsius (Integer) 
- Temperature 2 – the maximum temperature in degrees Fahrenheit or Celsius (Integer) 
- Humidity 1 – maximum humidity in percent, 0 to 99 (Integer) 
- Humidity 2 – minimum humidity in percent, 0 to 99 (Integer) 
- Elevation – feet or meters above sea level (Integer)

If there was precipitation on that day, the record will also have two additional columns

- Precipitation start time
- Precipitation end time

After verifying that the input file exists, it is opened, the data is read, and the following stats are printed to the console:
- Range of dates in the file
- Average high temperature
- Average low temperature
- Maximum high temperature (include date)
- Minimum low temperature (include date)
- Total rainfall
- How many days it rained
- The first day it rained
- The last day it rained
