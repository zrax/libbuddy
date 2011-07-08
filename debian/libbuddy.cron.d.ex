#
# Regular cron jobs for the libbuddy package
#
0 4	* * *	root	[ -x /usr/bin/libbuddy_maintenance ] && /usr/bin/libbuddy_maintenance
