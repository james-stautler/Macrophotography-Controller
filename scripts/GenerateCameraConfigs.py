import sys
import subprocess

def get_configs():

    try:
        result = subprocess.run(["gphoto2", "--list-config"], capture_output=True, text=True, check=True)
        paths = result.stdout.strip().split('\n')
        configs = list(set(path.split('/')[-1] for path in paths if path))

        print("AVAILABLE CONFIGS:\n")
        for config in configs:
            print(config)

    except subprocess.CalledProcessError:
        print("Error: Could not communicate with the camera\n")
        print("Make sure the camera is connected and on when running the script!\n")
    except FileNotFoundError:
        print("Error: 'gphoto2' not found. Please install it before running the script\n")


if __name__ == "__main__":
    get_configs()


    
    

