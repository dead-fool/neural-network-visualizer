# Neural Network Visualizer
The Neural Network Visualizer with OpenGL is a tool designed to visualize the activity data of a trained neural network using the MNIST dataset. This visualizer takes the activity data of from hidden layers of the neural network on 100 sample data. The neural network has been trained on 60k, of the MNIST dataset and provides an interactive 3D representation of the neural network's internal activations.

![image](https://github.com/dead-fool/neural-network-visualizer/assets/66507877/2e588af5-0a5f-4dcd-9061-ca12ca62fdc3)


## Features
* Parse .npz file of activity data saved as compressed numpy arrays.
* Visualize the activity data of a trained neural network's hidden layers.
* Interact with the 3D representation of neural network activations.
* Supports visualization of multiple hidden layers.
* Color mapping to represent activation intensity.
* Easy-to-use interface for exploring neural network behavior.

# Prerequisites
 Before using the Neural Network Visualizer, ensure you have the following:

* Trained neural network model (trained on MNIST) .
* Activity data for hidden layers (100 samples) as .npz file(example in the project).
* OpenGL
* GLFW
* IMGUI


# Credits
This project is inspired by the excellent work in neural network visualization and utilizes the power of OpenGL for interactive 3D graphics.
Heavily inspired by : Marijn van Vliet (https://github.com/wmvanvliet/scns/tree/main/visualizations/multilayer_perceptron).
The neural network model and the data record was highly influenced by her amazing project.


License
This project is licensed under the MIT License - see the LICENSE file for details.

Feel free to contribute to this project by submitting issues or pull requests. Happy visualizing!
