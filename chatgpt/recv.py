import mmap
from PIL import Image as im

def receive_from_cpp():
    # Open shared memory object
    shm = mmap.mmap(-1, data_size, "mat_data")

    # Read data from shared memory
    image = np.ndarray(shape=(rows, cols, 3), dtype=np.uint8, buffer=shm)

    # Do YOLO prediction on the image
    # boxes = yolo_predict(image)

    data = im.fromarray(image)
      
    # saving the final output 
    # as a PNG file
    data.save('gfg_dummy_pic.png')
    return boxes

def yolo_predict(image):
    # Do YOLO prediction on the image
    # ...

    # return boxes