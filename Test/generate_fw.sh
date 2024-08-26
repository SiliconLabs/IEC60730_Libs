#!/bin/bash

#./execute_test.sh $1 $2 $3 $4
# $1: task: all, gen-only, run-only
# $2: components: all, cpu_registers, programme_counter...
# $3: Platform: MG12, MG21, ZG23
# $4: Compiler: GCC, IAR
# $5: NON_SECURE_EN=1 or CRC_32=1, ...
#     APP_SECURE=true or false

# Example
# With GCC
# export TOOL_DIRS=../SimplicityStudio_v5/developer/toolchains/gnu_arm/10.3_2021.10/bin
# ./execute_test.sh all invariable_memory 440165484 MG21 GCC
# With IAR
# export TOOL_DIRS=../IAR/iar_bxarm_9204/arm/bin
# ./execute_test.sh all invariable_memory 440165484 MG21 IAR

# Note:
# In case you want to build CRC32 run this command. For example
# ./execute_test.sh all invariable_memory 440165484 MG21 GCC "CRC_32=1 NON_SECURE_EN=true N_CRC_DEBUG=1 APP_SECURE=true"

# Print console log
function print
{
    echo "=============== $1 ===============" | tee -a $LOG_FILE
}

# Print console log and timedate or summariz result
function print1
{
    DATE="[$(date)]"
    LOG="tee -a $LOG_FILE"
    echo | $LOG
    echo "================================================================================"  | $LOG
    if [ $# -ge 2 ]; then
        echo "= $DATE " | $LOG
        for arg in "$@"
        do
            echo -e "= $arg"  | $LOG
        done
    else
        echo -e "= $DATE $1"  | $LOG
    fi
    echo "================================================================================"  | $LOG
    echo  | $LOG
}

function gen_image
{

    if [ -e $LOG_FILE ];then
        rm -rf $LOG_FILE
    fi
    touch $LOG_FILE
    pushd ../Make > /dev/null
    if [[ "$1" = "all" ]]; then
        print1 "Generate all components!"
        print "Clean component"
        log=$(make clean_all)
        echo $log | tee -a $LOG_FILE
        data=$(make info)
        data=${data//"post bist integrated"/}
        list_component=${data:17}
        print $list_component
    else
        print "Generate only components: $1"
        print "Clean component: $1"
        log=$(make clean COMPONENT=$1 DERIVATIVE=$DERIVATIVE)

        print "$log"

        list_component="$1"
    fi
    print "Component list: ${list_component}"

    # Get Compiler and Arguments
    COMP=$2
    ARG=$3

    SECURE="S"
    non_secure=""
    if [[ "$ARG" == *"NON_SECURE_EN=true"* ]]; then
        SECURE="NS"
        non_secure="_NS"
    fi

    resultBuild=("\n======== Summariez the build results of all component ========\n")
    sumResultBuild=""
    for component in ${list_component}; do
        print1 "Start build component: $component" "Compiler: $COMP" "Arguments: $ARG"
        OUTPUT_PATH=$(pwd)/Build/$component/$DEVICE/$DERIVATIVE/$COMP/$SECURE/Out
        # log=$(make clean COMPONENT=$component DERIVATIVE=efr32mg21a020f1024im32)
        # echo $log | tee -a $LOG_FILE
        if [ "$component" == "cpu_registers" ] && [ $DEVICE == "efr32mg24" ];then
            print1 "\n==============================================================\n"
            echo "Build component: $component chip: EFR32MG24 set arguments: APP_SECURE=true"
            print1 "\n==============================================================\n"
            log=$(make build COMPONENT=$component DERIVATIVE=$DERIVATIVE "APP_SECURE=true" COMPILER=$COMP) # >> $LOG_FILE
        else
            log=$(make build COMPONENT=$component DERIVATIVE=$DERIVATIVE $ARG COMPILER=$COMP) # >> $LOG_FILE
        fi

        echo "$log" | tee -a $LOG_FILE
        result=$(tail -n 1 $LOG_FILE)

        crc=""
        if [ "$component" == "invariable_memory" ] || [ "$component" == "integrated" ]; then
            if [[ "$ARG" == *"N_CRC_DEBUG=1"* ]]; then
                use_crc_file=1
            fi

            if [[ "$ARG" == *"CRC_32=1"* ]]; then
                crc="_crc32"
            else
                crc="_crc16"
            fi
        fi

        file_out=iec60730_$component
        file_out_ns=iec60730_$component$non_secure
        file_out_ns_crc=iec60730_$component$non_secure$crc

        if [ "$result" = "Target compiled." ]; then
            print "Build successfully component: $component"
            resultBuild+=("Success to build component: $component\n")
            # pwd
            pushd $ARTIFACT_PATH > /dev/null
                print "Removing $file_out"
                rm -rf $file_out.s37
                rm -rf $file_out.lst
                rm -rf $file_out.axf
                rm -rf $file_out.hex
                rm -rf $file_out.bin
                print "Removing $file_out_ns"
                rm -rf $file_out_ns.s37
                rm -rf $file_out_ns.hex
                rm -rf $file_out_ns.bin
                print "Removing $file_out_ns_crc"
                rm -rf $file_out_ns_crc.s37
                rm -rf $file_out_ns_crc.hex
                rm -rf $file_out_ns_crc.bin
            popd > /dev/null
            pushd $OUTPUT_PATH > /dev/null
                print "Copying $file_out"
                cp $file_out.s37  $ARTIFACT_PATH
                if [ -f "$file_out.lst" ]; then
                    cp $file_out.lst  $ARTIFACT_PATH
                fi
                cp $file_out.axf  $ARTIFACT_PATH
                cp $file_out.hex  $ARTIFACT_PATH
                cp $file_out.bin  $ARTIFACT_PATH

                # Copy file ns
                print "Copying $file_out_ns"
                if [ -f "$file_out_ns.s37" ]; then
                    cp $file_out_ns.s37  $ARTIFACT_PATH
                fi
                if [ -f "$file_out_ns.hex" ]; then
                    cp $file_out_ns.hex  $ARTIFACT_PATH
                fi
                if [ -f "$file_out_ns.bin" ]; then
                    cp $file_out_ns.bin  $ARTIFACT_PATH
                fi
                if [ -f "$file_out_ns.lst" ]; then
                    cp $file_out_ns.lst  $ARTIFACT_PATH
                fi

                # Copy file with crc
                print "Copying $file_out_ns_crc"
                if [ -f "$file_out_ns_crc.s37" ]; then
                    cp $file_out_ns_crc.s37  $ARTIFACT_PATH
                fi
                if [ -f "$file_out_ns_crc.hex" ]; then
                    cp $file_out_ns_crc.hex  $ARTIFACT_PATH
                fi
                if [ -f "$file_out_ns_crc.bin" ]; then
                    cp $file_out_ns_crc.bin  $ARTIFACT_PATH
                fi
            popd > /dev/null
        else
            print "ERROR!!! Build component: $component fail"
            resultBuild+=("Fail to build component: $component\n")
        fi
    done
    for restBuild in "${resultBuild[@]}"
    do
        sumResultBuild="$sumResultBuild$restBuild\n"
    done
    # Print summariez the build results
    print1 "$sumResultBuild"
    popd > /dev/null
}

LOG_PATH=$(pwd)/log
LOG_FILE=$LOG_PATH/log.txt
ARTIFACT_PATH=$(pwd)/artifact

if [ "$3" == "MG21" ]; then
    CHIP=EFR32MG21AXXXF1024
    DERIVATIVE=efr32mg21a020f1024im32
    DEVICE=efr32mg21
elif [ "$3" == "MG12" ]; then
    CHIP=EFR32MG12PXXXF1024
    DERIVATIVE=efr32mg12p332f1024gl125
    DEVICE=efr32mg12p
elif [ "$3" == "ZG23" ]; then
    CHIP=EFR32ZG23BXXXF512
    DERIVATIVE=efr32zg23b010f512im48
    DEVICE=efr32zg23
elif [ "$3" == "FG23" ]; then
    CHIP=EFR32FG23BXXXF512
    DERIVATIVE=efr32fg23b020f512im48
    DEVICE=efr32fg23
elif [ "$3" == "MG24" ]; then
    CHIP=EFR32MG24BXXXF1536
    DERIVATIVE=efr32mg24b310f1536im48
    DEVICE=efr32mg24
else
    echo "Does not support platform: $3"
    exit
fi

# LST_PATH=$ARTIFACT_PATH
# LST_PATH=$(pwd)/../Build/cpu_registers/efr32mg21/efr32mg21a020f1024im32/Out
if [ ! -e "artifact" ];then
    mkdir -p artifact
fi
if [ ! -e "log" ];then
    mkdir -p log
fi
arg=${6//"%20"/" "}
gen_image "$2" "$4" "$arg"