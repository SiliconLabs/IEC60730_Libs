#!/bin/bash

#./execute_test.sh $1 $2 $3 $4 $5
# $1: task: all, gen-only, run-only
# $2: components: all, cpu_registers, programme_counter...
# $3: ADAPTER_SN
# $4: Platform: MG12, MG21, ZG23
# $5: Compiler: GCC, IAR
# $6: NON_SECURE_EN=1 or CRC_32=1, ...
# $7: APP_SECURE=true or false

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

function print
{
    echo "=============== $1 ===============" | tee -a $LOG_FILE
}

function gen_image
{

    if [ -e $LOG_FILE ];then
        rm -rf $LOG_FILE
    fi
    touch $LOG_FILE
    pushd ../Make > /dev/null
    if [[ "$1" = "all" ]]; then
        print "Generate all components!"
        print "Clean component"
        log=$(make clean_all)
        echo $log | tee -a $LOG_FILE
        data=$(make info)
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

    for component in ${list_component}; do
        print "Build component: $component with Compiler: $COMP Arguments: $ARG"
        OUTPUT_PATH=$(pwd)/../Build/$component/$DEVICE/$DERIVATIVE/$COMP/$SECURE/Out
        # log=$(make clean COMPONENT=$component DERIVATIVE=efr32mg21a020f1024im32)
        # echo $log | tee -a $LOG_FILE

        log=$(make build COMPONENT=$component DERIVATIVE=$DERIVATIVE $ARG COMPILER=$COMP) # >> $LOG_FILE
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
            print "Build successfully"
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
            print "ERROR!!! Build fail:$result"
        fi
    done
    popd > /dev/null
}

function flash_image
{
    print "Flash components: $1"
    list_component="$1"

    use_crc_file=0
    crc=""

    # Get Compiler and Arguments
    COMP=$2
    ARG=$3

    print "Flash with Compiler: $COMP Arguments: $ARG"

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

    non_secure=""
    use_non_secure=0
    if [[ "$ARG" == *"NON_SECURE_EN=true"* ]]; then
        non_secure="_NS"
        use_non_secure=1
    fi

    # Export PATH to commander directory
    COMMANDER="commander"

    file_out=iec60730_$component.s37
    file_out_ns=iec60730_$component$non_secure.s37
    file_out_ns_crc=iec60730_$component$non_secure$crc.s37

    pushd $ARTIFACT_PATH > /dev/null
    if [ -f $file_out ]; then
        print "Erase chip"
        result=$($COMMANDER device masserase --device $DEVICE --serialno $ADAPTER_SN)
        echo "result: $result"

        if [ $use_non_secure == 1 ]; then
            print "Flash $file_out"
            result=$($COMMANDER flash --device $DEVICE --serialno $ADAPTER_SN $file_out)
        fi

        if [ $use_crc_file == 1 ]; then
            print "Flash $file_out_ns_crc"
            result=$($COMMANDER flash --device $DEVICE --serialno $ADAPTER_SN $file_out_ns_crc)
        else
            print "Flash $file_out_ns"
            result=$($COMMANDER flash --device $DEVICE --serialno $ADAPTER_SN $file_out_ns)
        fi

        echo "result: $result"
        if [ "" = "$result" ]; then
            return 1
        else
            return 0
        fi
    else
        print "ERROR!!! Can not find iec60730_$component.s37"
        return 1
    fi
    popd > /dev/null
}

function run
{
    if [[ "$1" = "all" ]]; then
        print "Run all components!"
        pushd ../Make > /dev/null
        data=$(make info)
        popd > /dev/null
        list_component=${data:17}
    else
        print "Run only components: $1"
        list_component="$1"
    fi
    echo "Component list: ${list_component}"

    # Get Compiler and Arguments
    COMP=$2
    ARG=$3

    SECURE="S"
    if [[ "$ARG" == *"NON_SECURE_EN=true"* ]]; then
        SECURE="NS"
    fi

    print "Run with Compiler: $COMP Arguments: $ARG"

    for component in ${list_component}; do
        flash_image "$component" $COMP "$ARG"
        local flashResult=$?
        echo "flash Result: $flashResult"
        pushd $TEST_PATH > /dev/null
        local LST_PATH=$(pwd)/../../Build/$component/$DEVICE/$DERIVATIVE/$COMP/$SECURE/Out
        # echo "$LST_PATH"
        if [ -f "iec60730_$component.py" ] && [ -d "$LST_PATH" ] && [ "0" = "$flashResult" ];then
            print "Start run test: $component"
            log=$(CHIP=$CHIP ADAPTER_SN=$ADAPTER_SN LST_PATH=$LST_PATH JLINK_PATH=$JLINK_PATH python3 iec60730_$component.py $COMP $ARG)
            local successCount=0
            local totalTestcase=0
            for x in echo $log; do
                if [ "True" == "$x" ]; then
                    let successCount+=1
                fi
                if [ "TC:" == "$x" ]; then
                    let totalTestcase+=1
                fi

            done

            if [ "$successCount" == "$totalTestcase" ] && [ 0 != $totalTestcase ]; then
                print "Finish run test: $component - Success $successCount/$totalTestcase - PASS"
            else
                print "Finish run test: $component - Success $successCount/$totalTestcase - FAIL"
            fi
        else
            if [ "1" = "$flashResult" ]; then
                log="Flash fail"
            elif [ ! -f "iec60730_$component.py" ]; then
                log="There is no file iec60730_$component.py"
            elif [ ! -d "$LST_PATH" ]; then
                log="There is no path $LST_PATH"
            fi
            print "ERROR!!! Fail to run test for component: $component - $log"
        fi
        popd > /dev/null
    done
}

LOG_PATH=$(pwd)/../log
LOG_FILE=$LOG_PATH/log.txt
ARTIFACT_PATH=$(pwd)/../artifact

if [ "$4" == "MG21" ]; then
    CHIP=EFR32MG21AXXXF1024
    DERIVATIVE=efr32mg21a020f1024im32
    DEVICE=efr32mg21
elif [ "$4" == "MG12" ]; then
    CHIP=EFR32MG12PXXXF1024
    DERIVATIVE=efr32mg12p332f1024gl125
    DEVICE=efr32mg12p
elif [ "$4" == "ZG23" ]; then
    CHIP=EFR32ZG23BXXXF512
    DERIVATIVE=efr32zg23b010f512im48
    DEVICE=efr32zg23
elif [ "$4" == "FG23" ]; then
    CHIP=EFR32FG23BXXXF512
    DERIVATIVE=efr32fg23b020f512im48
    DEVICE=efr32fg23
else
    echo "Does not support platfrom: $4"
    exit
fi

ADAPTER_SN="$3"
# LST_PATH=$ARTIFACT_PATH
# LST_PATH=$(pwd)/../Build/cpu_registers/efr32mg21/efr32mg21a020f1024im32/Out
JLINK_PATH=/opt/SEGGER/JLink/libjlinkarm.so
TEST_PATH=$(pwd)/test_script
if [ ! -e "artifact" ];then
    mkdir -p artifact
fi
if [ ! -e "log" ];then
    mkdir -p log
fi

case "$1" in
    gen-only)
        gen_image "$2" "$5" "$6"
        ;;
    run-only)
        run "$2" "$5" "$6"
        ;;
    all)
        gen_image "$2" "$5" "$6"
        run "$2" "$5" "$6"
        ;;
    *)
        echo "Please choose one of those options:  gen-only ; run-only; all"
esac

