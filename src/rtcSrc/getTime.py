import datetime

a = datetime.datetime.now()

print a.timetuple().tm_year
print a.timetuple().tm_mon
print a.timetuple().tm_day
print a.timetuple().tm_hour
print a.timetuple().tm_min
print a.timetuple().tm_sec


# Time functions
# Set time and date on RTC. Only used one time in the alarms lifetime.
# Set time RTC. Sets hour and minute. Used for adjusting the clock
# getTimeRTC. Get hour and minute from RTC
# has minute elapsed? Checks RTC for new minute
