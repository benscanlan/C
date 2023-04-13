#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Activation function (sigmoid)
double sigmoid(double x) {
    return 1 / (1 + exp(-x));
}

// Derivative of activation function (sigmoid)
double sigmoid_derivative(double x) {
    return x * (1 - x);
}

// Neural network structure
typedef struct {
    double **weights; // Weight matrix
    double *biases; // Bias vector
    double *outputs; // Output vector
    int num_inputs; // Number of input neurons
    int num_hidden; // Number of hidden neurons
    int num_outputs; // Number of output neurons
} NeuralNet;

// Create a new neural network
NeuralNet* create_neural_net(int num_inputs, int num_hidden, int num_outputs) {
    NeuralNet *nn = malloc(sizeof(NeuralNet));
    nn->num_inputs = num_inputs;
    nn->num_hidden = num_hidden;
    nn->num_outputs = num_outputs;
    nn->weights = malloc(num_hidden * sizeof(double *));
    for (int i = 0; i < num_hidden; i++) {
        nn->weights[i] = malloc(num_inputs * sizeof(double));
        for (int j = 0; j < num_inputs; j++) {
            nn->weights[i][j] = (double)rand() / RAND_MAX * 2 - 1; // Random initialization between -1 and 1
        }
    }
    nn->biases = malloc((num_hidden + num_outputs) * sizeof(double));
    for (int i = 0; i < num_hidden + num_outputs; i++) {
        nn->biases[i] = (double)rand() / RAND_MAX * 2 - 1; // Random initialization between -1 and 1
    }
    nn->outputs = malloc((num_hidden + num_outputs) * sizeof(double));
    return nn;
}

// Destroy a neural network
void destroy_neural_net(NeuralNet *nn) {
    for (int i = 0; i < nn->num_hidden; i++) {
        free(nn->weights[i]);
    }
    free(nn->weights);
    free(nn->biases);
    free(nn->outputs);
    free(nn);
}

// Feed forward through the neural network
void feed_forward(NeuralNet *nn, double *inputs) {
    // Calculate hidden layer outputs
    for (int i = 0; i < nn->num_hidden; i++) {
        double sum = 0;
        for (int j = 0; j < nn->num_inputs; j++) {
            sum += inputs[j] * nn->weights[i][j];
        }
        nn->outputs[i] = sigmoid(sum + nn->biases[i]);
    }
    // Calculate output layer outputs
    for (int i = 0; i < nn->num_outputs; i++) {
        double sum = 0;
        for (int j = 0; j < nn->num_hidden; j++) {
            sum += nn->outputs[j] * nn->weights[nn->num_hidden+i][j];
        }
        nn->outputs[nn->num_hidden+i] = sigmoid(sum + nn->biases[nn->num_hidden+i]);
    }
}

int main() {
    // Example usage
    srand(time(NULL)); // Initialize random seed
    NeuralNet *nn = create_neural_net(2, 2, 1); // Create a neural network with 2 input neurons, 2 hidden neurons, and 1 output neuron
    double inputs

