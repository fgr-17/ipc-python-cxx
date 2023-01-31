#include <iostream>
#include <cstring>

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>

#include <gst/gst.h>
#include <gst/app/gstappsrc.h>

#include <opencv2/opencv.hpp>

void send_to_python(const void *data, int rows, int cols, int step) {
  // Open shared memory object
  int shm_fd = shm_open("mat_data", O_CREAT | O_RDWR, 0666);

  // Configure size of shared memory object
  int data_size = rows * step;
  ftruncate(shm_fd, data_size);

  // Map shared memory object to process address space
  void *ptr = mmap(0, data_size, PROT_WRITE, MAP_SHARED, shm_fd, 0);

  // Copy data to shared memory
  memcpy(ptr, data, data_size);

  // Unmap shared memory
  munmap(ptr, data_size);

  // Close shared memory object
  close(shm_fd);
}

/* The appsink has received a buffer */
static GstFlowReturn new_sample (GstElement *sink) {
  GstSample *sample;

  /* Retrieve the buffer */
  g_signal_emit_by_name (sink, "pull-sample", &sample);
  if (sample) {
    /* The only thing we do in this example is print a * to indicate a received buffer */
    GstBuffer *buffer = gst_sample_get_buffer(sample);

    // Get Mat from buffer
    GstMapInfo info;
    gst_buffer_map(buffer, &info, GST_MAP_READ);
    cv::Mat image(cv::Size(640, 480), CV_8UC3, info.data, cv::Mat::AUTO_STEP);

    // Send to Python
    send_to_python(image.data, image.rows, image.cols, image.step);

    gst_buffer_unmap(buffer, &info);
    gst_sample_unref (sample);
    return GST_FLOW_OK;
  }

  return GST_FLOW_ERROR;
}


/* This function is called when an error message is posted on the bus */
static void error_cb (GstBus *bus, GstMessage *msg) {
  GError *err;
  gchar *debug_info;

  /* Print error details on the screen */
  gst_message_parse_error (msg, &err, &debug_info);
  g_printerr ("Error received from element %s: %s\n", GST_OBJECT_NAME (msg->src), err->message);
  g_printerr ("Debugging information: %s\n", debug_info ? debug_info : "none");
  g_clear_error (&err);
  g_free (debug_info);

}


using namespace cv;

int main(int argc, char *argv[]) {
  gst_init(&argc, &argv);

  GMainLoop *main_loop;

  GstBus *bus;

  // Create pipeline
  GstElement *pipeline = gst_pipeline_new("pipeline");

  // Create source
  GstElement *src = gst_element_factory_make("videotestsrc", "src");
  gst_bin_add(GST_BIN(pipeline), src);

  // Create sink
  GstElement *sink = gst_element_factory_make("appsink", "sink");
  gst_bin_add(GST_BIN(pipeline), sink);

  /* Configure appsink */
  g_object_set (sink, "emit-signals", TRUE, NULL);
  g_signal_connect (sink, "new-sample", G_CALLBACK (new_sample), (void*) NULL );

  // Link elements
  gst_element_link(src, sink);

  bus = gst_element_get_bus (pipeline);
  gst_bus_add_signal_watch (bus);
  g_signal_connect (G_OBJECT (bus), "message::error", (GCallback)error_cb, (void*) NULL);
  gst_object_unref (bus);


  // Start pipeline
  gst_element_set_state(pipeline, GST_STATE_PLAYING);

  /* Create a GLib Main Loop and set it to run */
  main_loop = g_main_loop_new (NULL, FALSE);
  g_main_loop_run (main_loop);



  // Clean up
  gst_element_set_state(pipeline, GST_STATE_NULL);
  gst_object_unref(pipeline);

  return 0;
}


