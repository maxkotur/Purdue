#!/bin/bash

#Do not insert code here

#DO NOT REMOVE THE FOLLOWING TWO LINES
git add $0 >> .local.git.out
git commit -a -m "Lab 2 commit" >> .local.git.out
git push >> .local.git.out || echo

# cycles per second
hertz=$(getconf CLK_TCK)

function check_arguments {


	#If number of arguments is less than 4, exit. 
	if [ "$1" -lt 6 ]; then
		echo "USAGE: "
                echo "$0 {process id} -cpu {utilization percentage} -mem {maximum memory in kB} {time interval}"
                exit
        fi

	CPU_THRESHOLD=$4
	MEM_THRESHOLD=$6
}

function init
{

	PID=$1 #This is the pid we are going to monitor

	TIME_INTERVAL=${@:$#} #Time interval is the last argument

}

#This function calculates the CPU usage percentage given the clock ticks in the last $TIME_INTERVAL seconds
function jiffies_to_percentage {
	
	#Get the function arguments (oldstime, oldutime, newstime, newutime)
	oldutime=$1
  oldstime=$2
  newutime=$3
  newstime=$4

	#Calculate the elpased ticks between newstime and oldstime (diff_stime), and newutime and oldutime (diff_stime)
	diff_stime=$newstime-$oldstime
  diff_utime=$newutime-$oldutime

	#You will use the following command to calculate the CPU usage percentage. $TIME_INTERVAL is the user-provided time_interval
	#Note how we are using the "bc" command to perform floating point division

	echo "100 * ( ($diff_stime + $diff_utime) / $hertz) / $TIME_INTERVAL" | bc -l
}


#Returns a percentage representing the CPU usage
function calculate_cpu_usage {

	#CPU usage is measured over a periode of time. We will use the user-provided interval_time value to calculate 
	#the CPU usage for the last interval_time seconds. For example, if interval_time is 5 seconds, then, CPU usage
	#is measured over the last 5 seconds


	#First, get the current utime and stime (oldutime and oldstime) from /proc/{pid}/stat
	# $14 = utime %lu and $15 = stime %lu
	oldutime=$(cat /proc/$PID/stat | awk '{print $14}')
  oldstime=$(cat /proc/$PID/stat | awk '{print $15}')

	#Sleep for time_interval
	sleep $TIME_INTERVAL

	#Now, get the current utime and stime (newutime and newstime) /proc/{pid}/stat
	newutime=$(cat /proc/$PID/stat | awk '{print $14}')
  newstime=$(cat /proc/$PID/stat | awk '{print $15}')

	#The values we got so far are all in jiffier (not Hertz), we need to convert them to percentages, we will use the function
	#jiffies_to_percentage

	percentage=$(jiffies_to_percentage $oldutime $oldstime $newutime $newstime)


	#Return the usage percentage
	echo "$percentage" #return the CPU usage percentage
}

function calculate_mem_usage
{
	#Let us extract the VmRSS value from /proc/{pid}/status
	mem_usage=`cat /proc/$PID/status | grep VmRSS | awk '{print $2}'`

	#Return the memory usage
	echo "$mem_usage"
}

function notify
{
	#We convert the float representating the CPU usage to an integer for convenience. We will compare $usage_int to $CPU_THRESHOLD
	cpu_usage_int=$(printf "%.f" $1)

	#Check if the process has exceeded the thresholds
	if [ $cpu_usage_int -gt $CPU_THRESHOLD ]
	then
		echo "CPU Exceeded"
		touch email
		echo "CPU USAGE is greater than CPU THRESHOLD" >> email
		echo "Process ID: $PID " >> email
		echo "Process NAME: $(cat /proc/$PID/status | grep "Name" | awk '{print $2}')" >> email
		echo "CPU USAGE: $cpu_usage_int" >> email
		echo "MEMORY USAGE: $mem_usage" >> email
		/usr/bin/mailx -s "CPU Exceeded" $USER < email
		rm email
	fi

	#Check if process exceeded its CPU or MEM thresholds. 
	if [ $mem_usage -gt $MEM_THRESHOLD ]
	then
		echo "MEM Exceeded"
		touch email
		echo "MEMORY USAGE is greater than MEMORY THRESHOLD" >> email
		echo "Process ID: $PID" >> email
		echo "Process NAME: $(cat /proc/$PID/status | grep "Name" | awk '{print $2}')" >> email
		echo "CPU USAGE: $cpu_usage_int" >> email
		echo "MEMORY USAGE: $mem_usage" >> email
		/usr/bin/mailx -s "MEM Exceeded" $USER < email
		rm email
	fi
}


check_arguments $# $@

init $1 $@

echo "CPU THRESHOLD: $CPU_THRESHOLD"
echo "Time interval: $TIME_INTERVAL" 

#The monitor runs forever
while [ -n "$(ls /proc/$PID)" ] #While this process is alive
do
	#part 1
	cpu_usage=$(calculate_cpu_usage)

	#part 2
	mem_usage=$(calculate_mem_usage)

	#Call the notify function to send an email to $USER if the thresholds were exceeded
	notify $cpu_usage $mem_usage

done
