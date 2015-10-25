import random

PRINT_STEPS = True


class Node:
    def __init__(self, name):
        self.neighbors = dict()  # { other_node -> capacity }
        self.lookup_table = dict()  # { destination -> (which node this node sends to, total length) }
        self.name = str(name)  # for printing purposes only
        self.send_queue = list()  # [ (destination, packet_size) ]
        self.in_progress = list()  # [ {send_to, destination, amount_left, packet_size} ]
        self.recv_queue = dict()  # { (src, dest) -> cur_amount }

    def __repr__(self):
        return "Node " + str(self.name)

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
            if packet[0] in self.lookup_table:
                self.in_progress.append(
                    {
                        "send_to": self.lookup_table[packet[0]][0],
                        "destination": packet[0],
                        "amount_left": packet[1],
                        "packet_size": packet[1]
                    })
            else:
                print("IMPOSSIBLE TO ROUTE FROM "+str(self)+" TO "+str(packet[0]))
            self.send_queue.remove(packet)

    def process_queue(self):
        iteration_capacity = self.neighbors.copy()
        # transfer what you can
        for packet in self.in_progress:
            amount_possible = min(packet["amount_left"], iteration_capacity[packet["send_to"]])
            if amount_possible:
                if (self, packet["destination"]) not in packet["send_to"].recv_queue:
                    packet["send_to"].recv_queue[(self, packet["destination"])] = 0
                if packet["amount_left"] - amount_possible == 0:  # it finishes sending on this iteration
                    del packet["send_to"].recv_queue[(self, packet["destination"])]
                    if packet["send_to"] is not packet["destination"]:
                        packet["send_to"].send_queue.append((packet["destination"], packet["packet_size"]))
                packet["amount_left"] -= amount_possible
                iteration_capacity[packet["send_to"]] -= amount_possible
                if PRINT_STEPS:
                    print("Node "+self.name+" transferred "+str(amount_possible)+" to "+str(packet["send_to"])
                          +" (final dest: "+str(packet["destination"])+", left: "+str(packet["amount_left"])+")")

        # remove completed packets from queue
        for packet in self.in_progress[:]:
            if packet["amount_left"] == 0:
                self.in_progress.remove(packet)


    def loop_step(self):
        self.route_packets()
        self.process_queue()


def create_network(nodes=9, fixed_capacity=0):
    """
    :param nodes: how many nodes in the network
    :param fixed_capacity: should there be a fixed capacity between nodes (int)
    :return: list of Nodes, list of (node1, node2, capacity of link)
    """
    network = list()
    node_list = list()
    for i in range(nodes):
        node_list.append(Node(i))
    for i in range(len(node_list)):
        for j in range(i+1, len(node_list)):
            # add paths randomly between nodes
            if (nodes-1) and random.uniform(0, 1) < 1./(nodes-1):
                network.append((node_list[i], node_list[j], fixed_capacity if fixed_capacity else random.randint(1, 10)))

    # check if any nodes were left out
    for node in node_list:
        for link in network:
            if node is link[0] or node is link[1]:
                break
        else:
            network.append((node, random.choice(list(n for n in node_list if n is not node)), fixed_capacity if fixed_capacity else random.randint(1, 10)))
    if PRINT_STEPS:
        print("Created network with "+str(nodes)+" nodes.")
    return node_list, network


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


def send_packet(src, dest, size):
    src.send_queue.append((dest, size))


def network_active(node_list):
    for node in node_list:
        if node.send_queue or node.in_progress:
            return True


def main():
    node_list, network = create_network(nodes=9, fixed_capacity=1)
    set_up_network(node_list, network)

    packets_to_send = [  # (iteration#, source, dest, size)
        (0, node_list[0], node_list[1], 10),
        (0, node_list[0], node_list[2], 10),
        (0, node_list[0], node_list[3], 10),
        (0, node_list[0], node_list[4], 10)
    ]
    iteration_num = 0
    # MAIN LOOP
    while packets_to_send or network_active(node_list):
        # send packets if it's their turn
        for packet in packets_to_send[:]:
            if iteration_num == packet[0]:
                send_packet(*(packet[1:]))
                packets_to_send.remove(packet)
        for node in node_list:
            node.loop_step()
        iteration_num += 1
    print("Simulation took "+str(iteration_num)+" iterations")


if __name__ == "__main__":
    main()
