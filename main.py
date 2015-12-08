import csv

from network import Network
from packet import Packet

PRINT_STEPS = True


def load_packets_from_files(filename, node_list):
    packets = list()
    with open(filename) as csvfile:
        reader = csv.reader(csvfile)
        for row in reader:
            packets.append(Packet(int(row[0]), node_list[int(row[1])], node_list[int(row[2])], int(row[3])))
    return packets


def main(network_filename, packets_filename):
    network = Network(network_filename, PRINT_STEPS)
    packets = load_packets_from_files(packets_filename, network.node_list)
    iteration_num = 0

    # MAIN LOOP
    while [packet for packet in packets if packet.turn <= iteration_num and not packet.end_turn] or network.active():
        if PRINT_STEPS:
            print("ITERATION "+str(iteration_num+1))
        # send packets if it's their turn (sorted by smallest first)
        this_turn_packets = sorted([packet for packet in packets if packet.turn == iteration_num], key=lambda x: x.size)
        for packet in this_turn_packets:
            network.send_packet(packet)
        network.loop_step(iteration_num)
        iteration_num += 1

    # calculate and output end statistics
    total_time_waited = sum([p.time_waited for p in packets])
    slowdown = 0
    for packet in packets:
        slowdown += (packet.end_turn - packet.turn)/packet.size
    slowdown /= len(packets)
    print("Simulation took "+str(iteration_num)+" iterations. Mean Slowdown: "+str(slowdown)+". Total time waited: "+str(total_time_waited))
    return iteration_num, slowdown, total_time_waited


if __name__ == "__main__":
    with open("results.csv", "w") as f:
        # run an experiment for each distribution with varying numbers of tests each and output the average of the
        # iterations, slowdown, and wait time for all
        for name in ['paredo', 'normal', 'uniform']:
            trials = 10
            totalits = 0
            totalslowdown = 0
            totalwait = 0
            for x in range(10):
                iterations, slowdown, wait_time = main(network_filename="network.csv", packets_filename=name+".csv")
                totalits += iterations
                totalslowdown += slowdown
                totalwait += wait_time
            totalits /= trials
            totalslowdown /= trials
            totalwait /= trials
            f.write(name+","+str(totalits)+","+str(totalslowdown)+","+str(totalwait)+"\n")