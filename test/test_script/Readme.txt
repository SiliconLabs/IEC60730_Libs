1 #Before run
export CHIP=EFR32MG21AXXXF1024 ADAPTER_SN=440043402
export LST_PATH=~/devs_efx32_iec60730/Build/cpu_registers/efr32mg21/efr32mg21a020f1024im32/Out
export JLINK_PATH=/opt/SEGGER/JLink/libjlinkarm.so

#Run
python3 iec60730_programme_counter.py


2. #Or

CHIP=EFR32MG21AXXXF1024 ADAPTER_SN=440043402 LST_PATH=/home/admin-wfh/Downloads/devs_efx32_iec60730/Build/cpu_registers/efr32mg21/efr32mg21a020f1024im32/Out JLINK_PATH=/opt/SEGGER/JLink/libjlinkarm.so python3 iec60730_programme_counter.py


3 Note for CPU Testing
a. Non secure IAR MG21
LST_PATH=~/devs_efx32_iec60730/Build/cpu_registers/efr32mg21/efr32mg21a020f1024im32/IAR/NS/Out APP_TYPE=NonSecureApp python3 iec60730_cpu_registers.py IAR

b. Secure IAR MG21
LST_PATH=~/devs_efx32_iec60730/Build/cpu_registers/efr32mg21/efr32mg21a020f1024im32/IAR/S/Out APP_TYPE=SecureApp python3 iec60730_cpu_registers.py IAR

c. Non secure GCC MG21
LST_PATH=~/devs_efx32_iec60730/Build/cpu_registers/efr32mg21/efr32mg21a020f1024im32/IAR/NS/Out APP_TYPE=NonSecureApp python3 iec60730_cpu_registers.py IAR

d. Secure GCC MG21
LST_PATH=~/devs_efx32_iec60730/Build/cpu_registers/efr32mg21/efr32mg21a020f1024im32/IAR/S/Out APP_TYPE=SecureApp python3 iec60730_cpu_registers.py IAR

e. IAR MG12
LST_PATH=~/devs_efx32_iec60730/Build/cpu_registers/efr32mg12p/efr32mg12p332f1024gl125/IAR/S/Out APP_TYPE=SecureApp python3 iec60730_cpu_registers.py IAR

f. GCC MG12
LST_PATH=~/devs_efx32_iec60730/Build/cpu_registers/efr32mg12p/efr32mg12p332f1024gl125/GCC/S/Out APP_TYPE=SecureApp python3 iec60730_cpu_registers.py GCC