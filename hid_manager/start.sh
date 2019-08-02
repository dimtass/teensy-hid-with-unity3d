#!/bin/bash -e
PROG=hid_manager
TMP_FILE="/tmp/hid-shared-buffer"
: ${DEBUG:=}

cat <<EOF
    This script starts the HID manager. You need to connect
    the teensy via USB to your workstation and flash the proper
    firmware that works with this tool.
    More info here:
    https://www.stupid-projects.com/controlling-a-3d-object-in-unity3d-with-teensy-and-mpu-6050/

    Usage for no debugging mode:
    $ ./start.sh

    Usage for debugging mode (it prints the HID incoming data):
    $ DEBUG=1 ./start.sh
EOF

if [ ! -f "${PROG}" ]; then
    echo "Couldn't find the ${PROG}. Maybe you need to build it first, by running make"
    exit 1
fi

# Create a shared file
if [ ! -f "${TMP_FILE}" ]; then
    echo "Creating tmp shared buffer for HID data in ${TMP_FILE}"
    rm ${TMP_FILE}
    dd if=/dev/zero of="${TMP_FILE}" bs=64 count=1
fi

echo "Debug ouput is set to: ${DEBUG}"
echo "Starting HID manager..."
./hid_manager ${DEBUG}