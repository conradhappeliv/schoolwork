def get_num(i, j, size):
    return size*i + j


def put_to_file(num1, num2, already_done, f):
    if {num1, num2} not in already_done:
        f.write(str(num1)+","+str(num2)+",1\n")
        already_done.append({num1, num2})


def main(size):
    already_done = list()
    with open('./network.csv', 'w') as f:
        for i in range(size):
            for j in range(size):
                num = get_num(i, j, size)
                if i-1 >= 0:
                    put_to_file(num, get_num(i-1, j, size), already_done, f)
                if j-1 >= 0:
                    put_to_file(num, get_num(i, j-1, size), already_done, f)
                if i+1 < size:
                    put_to_file(num, get_num(i+1, j, size), already_done, f)
                if j+1 < size:
                    put_to_file(num, get_num(i, j+1, size), already_done, f)


if __name__ == "__main__":
    main(4)
