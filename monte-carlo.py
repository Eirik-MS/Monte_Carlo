import subprocess
import numpy as np
import matplotlib.pyplot as plt

def visualize_points(points, inside_count, total_points, pi_estimate):

    plt.figure(figsize=(6, 6))

    t = np.linspace(0, 2 * np.pi, 100)
    x_circle = np.cos(t)
    y_circle = np.sin(t)
    plt.plot(x_circle, y_circle, color='black')

    x_inside = [p[0] for p in points if p[2] == True]
    y_inside = [p[1] for p in points if p[2] == True]
    x_outside = [p[0] for p in points if p[2] == False]
    y_outside = [p[1] for p in points if p[2] == False]
    
    plt.scatter(x_inside, y_inside, color='blue', label='Inside Circle', s=10)
    plt.scatter(x_outside, y_outside, color='red', label='Outside Circle', s=10)
    plt.legend()
    plt.title(f"Monte Carlo Pi Estimation\nTotal Points: {total_points}, \nEstimated Pi: {pi_estimate} \nActual Pi: {np.pi}")
    plt.xlabel("X-axis")
    plt.ylabel("Y-axis")
    plt.xlim(-1, 1)
    plt.ylim(-1, 1)
    plt.show()

    
def main():

    ## try to run the cpp program monte-carlo-pi 

    result = subprocess.run(["./monte-carlo-pi", "1000000", "-s"], capture_output=True, text=True)
    if result.returncode != 0:
        print("Error running monte-carlo-pi:", result.stderr)
        return
    else:
        print("monte-carlo-pi output:", result.stdout)

    points = np.load("points.npy", allow_pickle=True)
    total_points = points[0]
    inside_count = points[1]  
    pi_estimate = points[2] 
    points = points[3:]

    

    print(f"inside_count: {inside_count}, total_points: {total_points}")
    print(f"pi_estimate: {pi_estimate}")
    print(f"First 5 points: {points[:5]}")
    
    if points.size == 0:
        print("No points loaded from points.npy")
        return
    
    #transform points into a list of tuples (x, y, inside)
    points = [(points[i], points[i+1], points[i+2]) for i in range(0, len(points), 3)]
    visualize_points(points, inside_count, total_points, pi_estimate)

if __name__ == "__main__":
    main()
