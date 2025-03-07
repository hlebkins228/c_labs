import matplotlib.pyplot as plot
import os


def get_averange_result_from_file(file_name):
    time_sum = 0
    numbers_count = 0
    with open(file_name, "r") as file:
        time_sum += int(file.readline())
        numbers_count += 1
    
    return time_sum // numbers_count


def create_plot():
    
    mysort_folder = "experiment_results_mysort"
    qsort_folder = "experiment_results_qsort"

    numbers_count_list = sorted([int(file[file.find("_") + 1: file.find(".")]) for file in os.listdir(mysort_folder)])
   
    y_values_mysort_list = [get_averange_result_from_file(f"{mysort_folder}/result_{amount}.txt") for amount in numbers_count_list]
    y_values_qsort_list = [get_averange_result_from_file(f"{qsort_folder}/result_{amount}.txt") for amount in numbers_count_list]

    x_values_list = numbers_count_list

    plot.plot(x_values_list, y_values_mysort_list)
    plot.plot(x_values_list, y_values_qsort_list)
    
    plot.title("Time experiment (sorted)")
    plot.ylabel("time, mcs")
    plot.xlabel("amount of numbers")
    plot.legend(["mysort", "qsort"])

    plot.grid()
    plot.show()


if __name__ == "__main__":
    create_plot()
