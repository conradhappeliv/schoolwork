import csv
import random

PRINT_STEPS = True


class Packet:
    def __init__(self, turn, source, dest, size):
        self.turn = turn
        self.end_turn = turn
        self.next_node = source
        self.source = source
        self.destination = dest
        self.amount_left = size
        self.size = size
        self.time_waited = 0
        self.path = list()

    def __repr__(self):
        return "Packet (Size "+self.size+", src: "+self.source+", dest: "+self.destination+")"


class Node:
    def __init__(self, name):
        self.neighbors = dict()  # { other_node -> capacity }
        self.lookup_table = dict()  # { destination -> (which node this node sends to, total length) }
        self.name = str(name)  # for printing purposes only
        self.send_queue = list()  # [ (destination, packet_size) ]
        self.in_progress = list()  # [ {send_to, destination, amount_left, packet_size} ]
        self.recv_queue = dict()  # { (src, dest) -> cur_amount }
        self.dont_do_yet = list()  # [ dest ]

    def __repr__(self):
        return "Node " + str(self.name)

    def __lt__(self, other):
        return self.name < other.name

    def get_adjacent_nodes(self, network):
        for link in network:
            if link[0] is self or link[1] is self:
                if link[0] is self:
                    self.neighbors[link[1]] = link[2]
                else:  # link[1] is self
                    self.neighbors[link[0]] = link[2]

    def add_lookup(self, destination, send_to, path_len):
        self.lookup_table[destination] = (send_to, path_len)

    def route_packets(self):
        for packet in self.send_queue[:]:
            for i in range(len(packet.path)):
                if packet.path[i] == self:
                    packet.next_node = packet.path[i+1]
                    self.in_progress.append(packet)
                    self.send_queue.remove(packet)
                    break
            else:
                print("IMPOSSIBLE TO ROUTE FROM "+str(self)+" TO "+str(packet.destination))

    def process_queue(self, iteration_num):
        iteration_capacity = self.neighbors.copy()
        # transfer what you can
        for packet in (p for p in self.in_progress if p.destination not in self.dont_do_yet):
            packet.time_waited += 1
            amount_possible = min(packet.amount_left, iteration_capacity[packet.next_node])
            if amount_possible:
                packet.time_waited -= 1
                if (self, packet.destination) not in packet.next_node.recv_queue:
                    packet.next_node.recv_queue[(self, packet.destination)] = 0
                if packet.amount_left - amount_possible == 0:  # it finishes sending on this iteration
                    del packet.next_node.recv_queue[(self, packet.destination)]
                    packet.next_node.dont_do_yet.append(packet.destination)
                    if packet.next_node is not packet.destination:
                        packet.next_node.send_queue.append(packet)
                packet.amount_left -= amount_possible
                iteration_capacity[packet.next_node] -= amount_possible
                if PRINT_STEPS:
                    print("Node "+self.name+" transferred "+str(amount_possible)+" to "+str(packet.next_node)
                          +" (final dest: "+str(packet.destination)+", left: "+str(packet.amount_left)+")")

        # remove completed packets from queue
        for packet in self.in_progress[:]:
            if packet.amount_left == 0:
                packet.amount_left = packet.size
                packet.end_turn = iteration_num
                self.in_progress.remove(packet)

    def loop_step(self, iteration_num):
        self.route_packets()
        self.process_queue(iteration_num)


def calculate_paths(node_list, source):
    """
    modified implementation of dijkstra's
    :param node_list:
    :param source:
    :return: { destination -> (first node on path, path length) }
    """
    result = {n: (None, float("inf")) for n in node_list}
    result[source] = (None, 0)
    node_list = node_list[:]  # make a copy for use in here
    while node_list:
        min_node = None
        min_node_dist = float("inf")

        # find min distanced node
        for node in node_list:
            if result[node][1] < min_node_dist:
                min_node = node
                min_node_dist = result[node][1]
        if min_node:  # check for disconnected graph
            node_list.remove(min_node)
            for neighbor, dist in min_node.neighbors.items():
                new_dist = result[min_node][1] + dist
                if new_dist < result[neighbor][1]:
                    if min_node is source or min_node in source.neighbors:
                        send_to = min_node
                    else:
                        send_to = result[min_node][0]
                    result[neighbor] = (send_to, new_dist)
        else:
            break

    return result


def set_up_network(node_list, network):
    for node in node_list:
        node.get_adjacent_nodes(network)
    for node in node_list:
        paths = calculate_paths(node_list, node)
        for dest, (send_to, path_len) in paths.items():
            if send_to:
                node.add_lookup(dest, send_to if send_to is not node else dest, path_len)
    if PRINT_STEPS:
        for node in node_list:
            for neighbor, path_len in node.neighbors.items():
                print(str(node)+" -> "+str(neighbor)+": "+str(path_len))


def find_or_create_node(name, node_list, names):
    if name not in names:
        new_node = Node(name)
        names.add(name)
        node_list.append(new_node)
        return new_node
    else:
        for node in node_list:
            if node.name == name:
                return node


def load_network_from_file(filename):
    node_list = list()
    network = list()
    names = set()
    with open(filename) as csvfile:
        reader = csv.reader(csvfile)
        for row in reader:
            node1 = find_or_create_node(row[0], node_list, names)
            node2 = find_or_create_node(row[1], node_list, names)
            network.append((node1, node2, int(row[2])))
    return node_list, network


def load_packets_from_files(filename, node_list):
    packets = list()
    with open(filename) as csvfile:
        reader = csv.reader(csvfile)
        for row in reader:
            packets.append(Packet(int(row[0]), node_list[int(row[1])], node_list[int(row[2])], int(row[3])))
    return packets


def send_packet(packet, taken_up):
    possibles = find_all_routes(packet.source, packet.destination)
    random.shuffle(possibles)
    possibles = sorted(possibles, key=lambda x: x[0])
    for possible in possibles:
        packet.path = possible[1]
        bad = False
        for i in range(len(packet.path) - 1):
            if i+1 < len(taken_up) and {packet.path[i], packet.path[i+1]} in taken_up[i+1]:
                bad = True
                break
        if not bad:
            break
    else:
        packet.path = possibles[0][1]

    if PRINT_STEPS: print("Packet from "+str(packet.source)+" to "+str(packet.destination)+" path: "+str(packet.path))

    for i in range(len(packet.path)-1):
        if i+2 > len(taken_up):
            taken_up.append(list())
        taken_up[i+1].append({packet.path[i], packet.path[i+1]})
    packet.source.send_queue.append(packet)


def network_active(node_list):
    for node in node_list:
        if node.send_queue or node.in_progress:
            return True


def find_possible_dests(source):
    return source.neighbors.keys()


def find_link_len(source, dest):
    return source.neighbors[dest]


routecache = {}
def find_all_routes(source, destination, cur_path=list(), cur_len=0):
    # return [(length, [path])...]
    if not cur_path: cur_path = [source]
    res = list()
    q = list(set(find_possible_dests(source)) - set(cur_path))
    random.shuffle(q)
    for place in q:
        cur_path.append(place)
        path_len = find_link_len(cur_path[-2], cur_path[-1])
        cur_len += path_len
        if cur_path[-1] is destination:
            res.append((cur_len, cur_path[:]))
        else:
            res.extend(find_all_routes(place, destination, cur_path, cur_len))
        cur_len -= path_len
        cur_path.pop()
    return res


def main(networkfilename, packetsfilename):
    node_list, network = load_network_from_file(networkfilename)
    set_up_network(node_list, network)
    packets_to_send = load_packets_from_files(packetsfilename, node_list)
    packets_sent = list()
    all_packets = [p for p in packets_to_send]
    iteration_num = 0
    taken_up = [[]]  # index is turn -> {set(): wait}

    # MAIN LOOP
    while packets_to_send or network_active(node_list):
        if PRINT_STEPS:
            print("ITERATION "+str(iteration_num+1))
        # send packets if it's their turn
        for packet in packets_to_send[:]:
            if iteration_num == packet.turn:
                send_packet(packet, taken_up)
                packets_sent.append(packet)
                packets_to_send.remove(packet)
        for node in node_list:
            node.loop_step(iteration_num)
        for node in node_list:
            node.dont_do_yet = list()
        iteration_num += 1
        if taken_up:
            taken_up.pop(0)
    total_time_waited = sum([p.time_waited for p in all_packets])
    slowdown = 0
    for packet in packets_sent:
        slowdown += (packet.end_turn - packet.turn)/packet.size
    slowdown /= len(packets_sent)
    print("Simulation took "+str(iteration_num)+" iterations. Mean Slowdown: "+str(slowdown)+". Total time waited: "+str(total_time_waited))
    return iteration_num, slowdown, total_time_waited


if __name__ == "__main__":
    with open("results.csv", "w") as f:
        for name in ['paredo', 'normal', 'uniform']:
            trials = 10
            totalits = 0
            totalslowdown = 0
            totalwait = 0
            for x in range(10):
                iterations, slowdown, wait_time = main(networkfilename="network.csv", packetsfilename=name+".csv")
                totalits += iterations
                totalslowdown += slowdown
                totalwait += wait_time
            totalits /= trials
            totalslowdown /= trials
            totalwait /= trials
            f.write(name+","+str(totalits)+","+str(totalslowdown)+","+str(totalwait)+"\n")