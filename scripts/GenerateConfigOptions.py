import subprocess
import sys

def get_config_details(config):

    print(f"--- Fetching details for: {config} ---")

    try:

        result = subprocess.run(["gphoto2", "--get-config", config], capture_output=True, text=True, check=True)
        output = result.stdout.split('\n')

        choices = []
        current_val = ""
        widget_type = ""

        for line in output:
            if line.startswith("Current:"):
                current_val = line.replace("Current: ", "").strip()
            elif line.startswith("Type:"):
                widget_type = line.replace("Type: ", "").strip()
            elif line.startswith("Choice:"):
                # Extract the choice text (skipping the index number)
                parts = line.split()
                if len(parts) >= 3:
                    choices.append(" ".join(parts[2:]))

        print(f"Type: {widget_type}")
        print(f"Current Value: {current_val}")
        print(f"Available Options ({len(choices)}):")
        for choice in choices:
            print(f"  - {choice}")
    
    except subprocess.CalledProcessError:
        print(f"Error: Could not connect to camera OR could not find configuration '{config}'.")

if __name__ == "__main__":

    if len(sys.argv) != 2:
        print("USAGE: GenerateConfigOptions.py [configOption]")
        exit(1)
    
    get_config_details(sys.argv[1])

