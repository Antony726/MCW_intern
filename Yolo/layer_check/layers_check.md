# Layers 

## Conv (1x48x160x160)
![alt text](image-2.png)
![alt text](image.png)
![alt text](image-1.png)

## Sigmoid
<!-- ![alt text](image-3.png) -->
![alt text](image-8.png)
<!-- ![alt text](image-4.png) -->
![alt text](image-9.png)

## Mul
![alt text](image-7.png)
![alt text](image-5.png)
![alt text](image-6.png)

## Add
![alt text](image-12.png)
![alt text](image-10.png)
![alt text](image-11.png)

## Concat
![alt text](image-15.png)
![alt text](image-13.png)
![alt text](image-14.png)

## Conv 1x1
![alt text](image-18.png)
![alt text](image-16.png)
![alt text](image-17.png)

## Split
![alt text](image-19.png)
![alt text](image-20.png)

## Resize 
![alt text](image-23.png)

![alt text](image-21.png)

![alt text](image-22.png)

## conv 3x3
![alt text](image-26.png)
![alt text](image-24.png)
![alt text](image-25.png)

## Sigmoid
![alt text](image-29.png)
![alt text](image-27.png)
![alt text](image-28.png)

## Mul
![alt text](image-30.png)
![alt text](image-31.png)
![alt text](image-32.png)

```python
import tensorflow as tf

input_shape = (96, 160, 160)
batch_size = 1


input_tensor1 = tf.keras.layers.Input(shape=input_shape, batch_size=batch_size, name="conv_output")
input_tensor2 = tf.keras.layers.Input(shape=input_shape, batch_size=batch_size, name="sigmoid_output")


mul_output = tf.keras.layers.Multiply(name="mul_layer")([input_tensor1, input_tensor2])


model = tf.keras.Model(inputs=[input_tensor1, input_tensor2], outputs=mul_output)

converter = tf.lite.TFLiteConverter.from_keras_model(model)
converter.target_spec.supported_ops = [tf.lite.OpsSet.TFLITE_BUILTINS]
tflite_model = converter.convert()


with open("mul_1x1.tflite", "wb") as f:
    f.write(tflite_model)

print(" TFLite model saved as mul_1x1.tflite")
```

## MUL
![alt text](image-33.png)
![alt text](image-34.png)
![alt text](image-35.png)

```python 
import tensorflow as tf

input_tensor1 = tf.keras.Input(shape=(80, 80, 96), batch_size=1, name="input_1")
input_tensor2 = tf.keras.Input(shape=(80, 80, 96), batch_size=1, name="input_2")

permute_to_nchw_1 = tf.keras.layers.Permute((3, 1, 2))(input_tensor1)
permute_to_nchw_2 = tf.keras.layers.Permute((3, 1, 2))(input_tensor2)

mul_output = tf.keras.layers.Multiply()([permute_to_nchw_1, permute_to_nchw_2])

permute_to_nhwc = tf.keras.layers.Permute((2, 3, 1))(mul_output)

model = tf.keras.Model(inputs=[input_tensor1, input_tensor2], outputs=permute_to_nhwc)

converter = tf.lite.TFLiteConverter.from_keras_model(model)
tflite_model = converter.convert()

with open("mul_new.tflite", "wb") as f:
    f.write(tflite_model)

print("TFLite model saved as mul_nchw.tflite")
```