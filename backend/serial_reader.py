import time
import serial

# Serial port settings
PORT = "COM4"          
BAUD_RATE = 115200    


def parse_packet(line):
    """
    Converts a telemetry string into a Python dictionary.

    Input:
    "SPEED=32.4,THROTTLE=0.62,RPM=4120"

    Output:
    {
        'SPEED': 32.4,
        'THROTTLE': 0.62,
        'RPM': 4120
    }
    """

    data = {}                      # Dictionary to store parsed values
    parts = line.split(",")        # Split packet into key=value pairs

    for part in parts:
        key, value = part.split("=")

        # Convert numbers to the correct type
        # Floats contain a decimal point, ints do not
        if "." in value:
            data[key] = float(value)
        else:
            data[key] = int(value)

    return data


def main():
    # Attempt to open the serial port
    try:
        ser = serial.Serial(PORT, BAUD_RATE, timeout=1)

        # Allow time for Arduino to reset after serial connection opens
        time.sleep(2)

        print("Connected to serial port.")

    except serial.SerialException as e:
        # Serial port failed to open
        print("Serial connection failed:", e)
        return

    # Main read loop (runs indefinitely)
    while True:
        try:
            # Read a full line from serial
            raw_line = ser.readline()

            # Decode bytes -> string and remove whitespace/newline
            raw_line = raw_line.decode("utf-8").strip()

            if not raw_line:
                continue

            # Parse telemetry into structured data
            telemetry = parse_packet(raw_line)

            # For now, just print the parsed data
            print(telemetry)

        except ValueError:
            # Raised if parsing fails (bad packet format)
            # We ignore the packet and keep running
            continue

        except KeyboardInterrupt:
            # Allow clean exit with Ctrl+C
            print("Exiting.")
            break

        except Exception as e:
            # Catch-all safety net
            # Prevents the program from crashing unexpectedly
            print("Unexpected error:", e)
            time.sleep(1)
