#!/bin/bash

#Do not insert code here

#DO NOT REMOVE THE FOLLOWING TWO LINES
git add $0 >> .local.git.out
git commit -a -m "Lab 2 commit" >> .local.git.out
git push >> .local.git.out || echo

# cycles per second
hertz=$(getconf CLK_TCK)

function check_arguments () {

  #Extract arguments
  
  echo "Extract arguments..."

}

function init () {

  echo "Init..."
  SORT=$2
  NUM_PROCESS=$4
  TIME_INTERVAL=$6
  ALL=$7
  
}

#This function calculates the CPU usage percentage given the clock ticks in the last $TIME_INTERVAL seconds
function jiffies_to_percentage () {
  #Get the function arguments (oldstime, oldutime, newstime, newutime)
	oldstime=$1
  oldutime=$2
  newstime=$3
  newutime=$4

	#Calculate the elpased ticks between newstime and oldstime (diff_stime), and newutime and oldutime (diff_stime)
  length=${#newstime[@]}
  for ((i=0;i<$length;i++)); do
    diff_stime=$(( ${newstime[$i]} - ${oldstime[$i]} ))
    diff_utime=$(( ${newutime[$i]} - ${oldutime[$i]} ))
    PERC=$(echo "100 * ( ($diff_stime + $diff_utime) / $hertz) / $TIME_INTERVAL" | bc -l)
    if [[ $PERC == "0" ]]; then
      PERC="0.0"
    elif [[ ${PERC:0:1} == "." ]]; then
      PERC="0$PERC"
    fi
    
    PERC=$(echo $PERC | cut -c1-3)
    percentage+=($PERC)
  done
  
  #You will use the following command to calculate the CPU usage percentage. $TIME_INTERVAL is the user-provided time_interval
	#Note how we are using the "bc" command to perform floating point division
}

#Returns a percentage representing the CPU usage
function calculate_cpu_usage () {

	#CPU usage is measured over a periode of time. We will use the user-provided interval_time value to calculate 
	#the CPU usage for the last interval_time seconds. For example, if interval_time is 5 seconds, then, CPU usage
	#is measured over the last 5 seconds
  declare -a oldutime
  declare -a oldstime
  declare -a newutime
  declare -a newstime
  LOOP=0
  
  
	#First, get the current utime and stime (oldutime and oldstime) from /proc/{pid}/stat
  for i in $PROCESS; do
    TIME=$(cat /proc/$i/stat 2> /dev/null)
    if [ $? != 0 ] ; then
      PROCESS=${PROCESS//$i/}
      USERN[$LOOP]="-"
      continue
    fi
    procs+=($i)
    oldutime+=($(cat /proc/$i/stat | awk '{print $14}'))
    oldstime+=($(cat /proc/$i/stat | awk '{print $15}'))
    LOOP=$(( $LOOP + 1 ))
  done

	#Sleep for time_interval
  sleep $TIME_INTERVAL
  
	#Now, get the current utime and stime (newutime and newstime) /proc/{pid}/stat
  for i in $PROCESS; do
    TIME=$(cat /proc/$i/stat 2> /dev/null)
    if [ $? != 0 ] ; then
      continue
    fi
    newutime+=($(cat /proc/$i/stat | awk '{print $14}'))
    newstime+=($(cat /proc/$i/stat | awk '{print $15}'))
  done

	#The values we got so far are all in jiffier (not Hertz), we need to convert them to percentages, we will use the function
	#jiffies_to_percentage
	jiffies_to_percentage $oldutime $oldstime $newutime $newstime 

	#Return the usage percentage
	# echo "$percentage" #return the CPU usage percentage
}


#This function takes as arguments the cpu usage and the memory usage that were last computed
function generate_top_report () {
  
  echo "Top report..."
  
  PROCESS=$(ls -al /proc 2> /dev/null | awk '{print $9, "\n"}' | egrep '([0-9])')
  calculate_tasks
  calculate_cpu_per
  calculate_mem_swap
  
  echo "============================================================================================"
  echo "top -$(uptime)" 
  echo "%Cpu(s): $US us,  $SY sy,  $NI ni,  $ID id,  $WA wa,  $HI hi,  $SI si,  $ST st"
  echo "Tasks: $TOTAL total, $RUNNING running, $SLEEPING sleeping, $STOPPED stopped, $ZOMBIE zombie"
  echo "KiB Mem : $MEM_TOTAL+total, $MEM_FREE+free, $MEM_USED used, $CACHE buff/cache"
  echo "KiB Swap: $SWAP_TOTAL+total, $SWAP_FREE+free, $SWAP_USED used. $AVAIL_MEM+avail Mem"
  echo ""
  echo "PID    USER   PR  NI  VIRT    RES    SHR    S %CPU  %MEM  TIME+   COMMAND"
  
  declare -a USERN
  
  if [[ $ALL == "-a" ]]; then
    PROCESS=$(ls -al /proc 2> /dev/null | awk '{print $9, "\n"}' | egrep '([0-9])')
    USERS=$(ls -al /proc 2> /dev/null | awk '{print $9 " " $3}' | egrep '([0-9])' | awk '{print $2}')
    for i in $USERS; do
      USERN+=($i)
    done
  else 
    PROCESS=$(ls -al /proc 2> /dev/null | egrep $USER | awk '{print $9}')
  fi
  
  declare -a procs
  declare -a NAMES
  declare -a percentage
  
  calculate_cpu_usage
  if [[ !($ALL == "-a") ]]; then
    for i in $PROCESS; do
      NAMES+=("$USER")
    done
  elif [[ $ALL == "-a" ]]; then
    USERN=${USERN//"-"}
    NAMES=$USERN
  fi
  calculate_line
  create_files
}

function create_files() {
  printf "%s\n" "${procs[@]}" > procs.txt
  printf "%s\n" "${NAMES[@]}" > names.txt
  printf "%s\n" "${PR[@]}" > pr.txt
  printf "%s\n" "${NI[@]}" > ni.txt
  printf "%s\n" "${VIRT[@]}" > virt.txt
  printf "%s\n" "${RES[@]}" > res.txt
  printf "%s\n" "${SHR[@]}" > shr.txt
  printf "%s\n" "${STATES[@]}" > states.txt
  printf "%s\n" "${percentage[@]}" > percentage.txt
  printf "%s\n" "${MEM[@]}" > mem.txt
  printf "%s\n" "${TIME[@]}" > time.txt
  printf "%s\n" "${CMD[@]}" > cmd.txt
  paste -d' ' procs.txt names.txt pr.txt ni.txt virt.txt res.txt shr.txt states.txt percentage.txt mem.txt time.txt cmd.txt > all.txt
  column -t -s' ' all.txt > table.txt
  if [[ $SORT == "-c" ]]; then
    sort -k 9 -n -r table.txt > final.txt
  elif [[ $SORT == "-m" ]]; then
    sort -k 5 -n -r table.txt > final.txt
  fi
  head -$NUM_PROCESS final.txt
  rm *.txt
}

# returns cpu%
function calculate_cpu_per() {
  US=$(mpstat | sed -n '4 p' | awk '{printf ("%0.1f", $4)}')
  SY=$(mpstat | sed -n '4 p' | awk '{printf ("%0.1f", $6)}')
  NI=$(mpstat | sed -n '4 p' | awk '{printf ("%0.1f", $5)}')
  ID=$(mpstat | sed -n '4 p' | awk '{printf ("%0.1f", $13)}')
  WA=$(mpstat | sed -n '4 p' | awk '{printf ("%0.1f", $7)}')
  HI=$(mpstat | sed -n '4 p' | awk '{printf ("%0.1f", $8)}')
  SI=$(mpstat | sed -n '4 p' | awk '{printf ("%0.1f", $9)}')
  ST=$(mpstat | sed -n '4 p' | awk '{printf ("%0.1f", $10)}')
}

# returns KiB Mem and Swap
function calculate_mem_swap() {
  MEM_TOTAL=$(cat /proc/meminfo | sed -n '1 p' | awk '{print $2}')
  MEM_FREE=$(cat /proc/meminfo | sed -n '2 p' | awk '{print $2}')
  MEM_USED=$((MEM_TOTAL-MEM_FREE))
  CACHE=$(cat /proc/meminfo | sed -n '5 p' | awk '{print $2}')
  SWAP_TOTAL=$(cat /proc/meminfo | sed -n '15 p' | awk '{print $2}')
  SWAP_FREE=$(cat /proc/meminfo | sed -n '16 p' | awk '{print $2}')
  SWAP_USED=$((SWAP_TOTAL-SWAP_FREE))
  AVAIL_MEM=$(cat /proc/meminfo | sed -n '3 p' | awk '{print $2}')
}

# Returns the tasks of the processes
function calculate_tasks() {
  
  TOTAL=0
  RUNNING=0
  SLEEPING=0
  STOPPED=0
  ZOMBIE=0
  
  for i in $PROCESS; do
    STATE=$(cat /proc/$i/stat 2> /dev/null | awk '{print $3}')
    TOTAL=$(( $TOTAL + 1 ))
    if [[ !($STATE =~ [SRTZID]) ]] ; then
      continue
    fi
    if [[ $STATE == "S" ]]
    then
      SLEEPING=$(( $SLEEPING + 1 ))
    elif [[ $STATE == "R" ]]
    then
      RUNNING=$(( $RUNNING + 1 ))
    elif [[ $STATE == "T" ]]
    then
      STOPPED=$(( $STOPPED + 1 ))
    elif [[ $STATE == "Z" ]]
    then
      ZOMBIE=$(( $ZOMBIE + 1 ))
    fi
  done
  
}

function calculate_line() {
  
  PR=()
  NI=()
  VIRT=()
  RES=()
  SHR=()
  CMD=()
  STATES=()
  TIME=()
  MEM=()
  
  MEM_TOTAL=$(cat /proc/meminfo | sed -n '1 p' | awk '{print $2}')
  
  for i in $PROCESS; do
    STAT=$(cat /proc/$i/stat 2> /dev/null)
    if [ $? != 0 ] ; then
      PROCESS=${PROCESS//$i/}
      continue
    fi
    P=$(echo $STAT | awk '{print $18}')
    if [[ $P -eq -100 ]]; then
      P="rt"
    fi
    PR+=($P)
    NI+=($(echo $STAT | awk '{print $19}'))
    CMD+=($(cat /proc/$i/status | grep "Name" | awk '{print $2}'))
    VIRT+=($(echo $STAT | awk '{print int($23/1000)}'))
    RES+=($(echo $STAT | awk '{print $24}'))
    STATES+=($(echo $STAT | awk '{print $3}'))
    RFI=$(cat /proc/$i/status | grep "RssFile" | awk '{print $2}')
    RSCH=$(cat /proc/$i/status | grep "RssShmem" | awk '{print $2}')
    SHR+=($(( $RFI + $RSCH )))
    T=$(echo $STAT | awk '{ print ($14+$15)/100 }')
    get_time $T
    TIME+=("$T")
    M=$(cat /proc/$i/status | grep "VmSize" | awk '{print $2}')
    MP=$(echo "scale=1; 100*($M/$MEM_TOTAL)" | bc)
    if [[ "$MP" == "0" ]]; then
      MP="0.0"
    elif [[ "${MP:1}" == "." ]] ; then
      MP="0$MP"
    fi
    MEM+=($MP)
  done
}

function get_time() {
  FIR=${T%.*}
  if [[ $FIR -ge 60 ]]; then
    FIR=${T%.*}
    MIN=(`expr $FIR / 60`)
    SEC=`expr $FIR % 60`
    if [[ $SEC -lt 10 ]]; then
      SEC="0$SEC"
    fi
    IFS="."
    read -ra AR <<< "$T"
    T="$MIN:$SEC."${AR[1]}""
    IFS=" "
  elif [[ $FIR -ge 10 ]]; then
    T="0:$T"
  elif [[ $FIR -ge 0 ]] && [[ "${#T}" -gt 1 ]]; then
    T="0:0$T"
    if [[ "${#T}" -lt 7 ]]; then
      T="$T"0""
    fi
  else
    T="0:00.00"
  fi
}

check_arguments $# $@

init $1 $@

#procmon runs forever or until ctrl-c is pressed.
while [ -n "$(ls /proc/$PID)" ] #While this process is alive
do
	generate_top_report
	sleep 10
done