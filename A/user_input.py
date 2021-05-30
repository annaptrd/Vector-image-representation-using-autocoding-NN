
def user_input():
    val = -1
    while val <= 0:
        input_data = input()
        try:
            val = int(input_data)  # an einai int proxwraei
        except ValueError:
            try:
                val = float(input_data)  # an einai float proxwraei
            except ValueError:
                val = -1   # alliws ginetai -1 kai ksanapairnei times
        if val <= 0:
            print("Error: please give a positive integer.")
    return val
