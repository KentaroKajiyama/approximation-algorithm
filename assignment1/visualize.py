import matplotlib.pyplot as plt
import os

CWD = os.getcwd()
def main():
  # Load the data from the result files
  opt_path = os.path.join(CWD,"assignment1\\OPT.txt")
  sol_path = os.path.join(CWD,"assignment1\\SOL.txt")
  with open(opt_path,"r") as f:
    opt_data_string = f.read().splitlines()
  opt_data = [int(element) for element in opt_data_string]
  with open(sol_path,"r") as f:
    sol_data_string = f.read().splitlines()
  sol_data = [int(element) for element in sol_data_string]
  # Convert to the quotient of sol/opt
  quotient_data = [sol/opt for sol,opt in zip(sol_data,opt_data)]
  #Find minimum value and its index
  min_value = min(quotient_data)
  min_index = quotient_data.index(min_value)
  average_value = sum(quotient_data)/len(quotient_data)
  # Plot the data
  plt.plot(quotient_data, label="SOL/OPT")
  plt.scatter(min_index, min_value, color="red", s=100, label="M:minimum value")
  plt.axhline(y=0.5, color="gray", linestyle='--', label="SOL/OPT=1/2")
  plt.axhline(y=average_value, color="yellow", label="A:average(SOL/OPT)")
  # Add labels and legend
  plt.title("SOL/OPT")
  plt.xlabel("Index")
  plt.ylabel("SOL/OPT")
  plt.legend()
  plt.show()

if __name__ == "__main__":
  main()