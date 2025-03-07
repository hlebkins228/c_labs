import os
from sys import argv
from random import randint
from progress.bar import ChargingBar


dataset_folder = "dataset_sorted"
cases_folder_name = "numbers_"
test_file_name = "case_"
results_folder_name = "experiment_results_qsort"


def pretty_function_complete_print(func):
    def wrapper(*args, **kwargs):
        print("\n")
        func(*args, **kwargs)
        print("\n--- \u001b[32mComplete\u001b[0m ---\n")
    
    return wrapper


@pretty_function_complete_print
def create_dataset(start_value, end_value, step, case_count, min_number=-1000, max_number=1000):
    try: 
        os.mkdir(dataset_folder)
    except FileExistsError:
        pass

    bar = ChargingBar("\u001b[36;1mdataset create\u001b[0m", max=((end_value - start_value) // step) * case_count)
    
    for numbers_count in range(start_value, end_value + 1, step):
        path = f"{dataset_folder}/{cases_folder_name}{numbers_count}"
        try: 
            os.mkdir(path)
        except FileExistsError:
            pass

        for case_number in range(case_count):
            file_name = path + "/" + test_file_name + str(case_number) + ".txt"
            with open(file_name, "w") as file:
                # data_list = [str(randint(min_number, max_number)) + "\n" for _ in range(numbers_count)]
                data_list = [str(i) + "\n" for i in range(numbers_count)]
                file.writelines(data_list)
                data_list.clear()

            bar.next()

    bar.finish()


@pretty_function_complete_print
def init_experiment(exec_file_name):
    try: 
        os.mkdir(results_folder_name)
    except FileExistsError:
        pass
    
    first_folder = os.listdir(dataset_folder)[0]
    tests_count = len(os.listdir(dataset_folder)) * len(os.listdir(f"{dataset_folder}/{first_folder}"))

    bar = ChargingBar("\u001b[36;1mtime measurement\u001b[0m", max=tests_count)

    for folder in os.listdir(dataset_folder):
        in_files_folder_path = f"{dataset_folder}/{folder}"
        for case_file in os.listdir(in_files_folder_path):
            case_file_path = in_files_folder_path + "/" + case_file
            result_file_path = results_folder_name + "/result_" + folder[folder.find("_") + 1:] + ".txt"
            
            os.system(f"./{exec_file_name} {case_file_path} {result_file_path}")
            bar.next()

    bar.finish()


def print_exec_line():
    print("exec line: python3 example.py <mode=data|time> start_value end_value step case_count [min_number max_number]")


if __name__ ==  "__main__":
    args_count = len(argv)
    if not ((argv[1] == "data" and (args_count == 6 or args_count == 8)) or (argv[1] == "time" and args_count == 3)):
        print_exec_line()
    else:
        if argv[1] == "data":
            try:
                argv = argv[2:]
                argv = list(map(int, argv))
                if (len(argv) == 4):
                    create_dataset(argv[0], argv[1], argv[2], argv[3])
                else:
                    create_dataset(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5])

            except (ValueError, TypeError):
                print("Invalid args!")
                print_exec_line()
        else:
            init_experiment(argv[2])