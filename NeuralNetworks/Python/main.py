import tensorflow as tf
import numpy as np

print(tf.__version__)

numpy_array = np.arange(1, 25, dtype=np.int32)

numpy_tensor = tf.constant(numpy_array, shape=[2, 4, 3])

print(numpy_tensor)
print(tf.config.list_physical_devices())

# Project Handwriting Recognition

mnist = tf.keras.datasets.mnist
(x_train, y_train), (x_test, y_test) = mnist.load_data()
(x_train, x_test) = x_train/255, x_test/255

# x_train: Picture, y_train Digit 

# Loading the Model:
model = tf.keras.models.load_model("my_model")
print(model)

predictions = model(x_train[:1])
print(predictions)
tf.nn.softmax(predictions)
simple_arr = predictions.numpy()[0].tolist()
print(simple_arr.index(max(simple_arr)))
print(y_train[:1])

loss_fn = tf.keras.losses.SparseCategoricalCrossentropy(from_logits=True)
#model.compile(optimizer="adam", loss=loss_fn, metrics=["accuracy"])
#model.fit(x_train, y_train, epochs=5)

# Safe Model:
#model.save("my_model")

print(model.evaluate(x_test, y_test, verbose=2))

probability_model = tf.keras.Sequential([model, tf.keras.layers.Softmax()])

print("Original ->", y_test[0])
output = probability_model(x_test[0:1])
output = output.numpy()[0].tolist()
print("Predicted ->", output.index(max(output)))

