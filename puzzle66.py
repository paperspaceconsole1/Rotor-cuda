import random
from bitcoin import *
import multiprocessing
import argparse
import time

def generate_address():
    low  = 0x20000000000000000
    high = 0x3ffffffffffffffff
    val = str(hex(random.randrange(low, high)))[2:]
    result = val.rjust(47 + len(val), '0')
    priv = result
    pub = privtopub(priv)
    pubkey1 = encode_pubkey(privtopub(priv), "bin_compressed")
    addr = pubtoaddr(pubkey1)
    return addr, result

def check_address():
    start_time = time.time()
    keys_generated = 0
    g = 0  # Initialize the value of g

    while True:
        addr, result = generate_address()
        keys_generated += 1

        if addr == '13zb1hQbWVsc2S7ZTZnP2G4undNNpdh5so':
            print("found!!", addr, result)
            k1 = result
            k2 = privtopub(result)
            k3 = addr

            file = open('boom.txt', 'a')
            file.write("Private key: " + k1 + '\n' + "Public key: " + k2 + '\n' + "Address: " + k3 + '\n\n')    
            file.close()
            
            break  # Stop the loop when the result is found

        else:
            elapsed_time = time.time() - start_time
            if elapsed_time >= 1:  # Check elapsed time every second
                speed = keys_generated / elapsed_time  # Calculate speed (keys generated per second)
                g = speed  # Assign the value of speed to g
                keys_generated = 0
                start_time = time.time()
            
            print(f"searching...", addr, result, f"Speed: {g:.2f} keys/second")

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('-t', '--cpus', type=int, default=multiprocessing.cpu_count(),
                        help='Number of CPUs to use')
    args = parser.parse_args()

    num_processes = args.cpus
    processes = []
    
    for _ in range(num_processes):
        p = multiprocessing.Process(target=check_address)
        p.start()
        processes.append(p)
    
    for p in processes:
        p.join()
