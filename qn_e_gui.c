/*
Name: Ashraf Mohammed Hassan Anil
Reg No: SCT211-0255/2021
UNIT : ICS2305
*/
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h> // be able to get the GUI app
#include <cairo.h> // perform actual drawing
/*
NOTE: If program is run on Vs code then have to configure the .json or create another 
.json file in .vscode directory then 
specify the included paths and compiler flags for GTK3:
*/
/*
Define data points to 10 ; relatively small number
so as to be noticeable when graphed on the gui
the 10 will represent last 10 cpu usage then use 
cairo to draw line to represent the curve
this is dependent on one machine; machine that has more processes using it
gives better result
*/
#define NUM_DATA_POINTS 10

double cpu_usage_history[NUM_DATA_POINTS] = {0.0};
int graph_index = 0;  // use graph_index not index to avoid conflicting with exisiting named vars from some header files above

// Function to draw the CPU usage graph
gboolean draw_cpu_graph(GtkWidget *drawing_area, cairo_t *cr) {
    // Clear the drawing area
    cairo_set_source_rgb(cr, 1, 1, 1); // Clear with white
    cairo_paint(cr);

    // Draw the CPU usage graph
    cairo_set_source_rgb(cr, 0, 0, 0); // Graph color (black)
    cairo_set_line_width(cr, 1);

    // Start drawing the graph
    cairo_move_to(cr, 0, 400); // Move to the bottom-left corner
    for (int i = 0; i < NUM_DATA_POINTS; i++) {
        cairo_line_to(cr, i * 80, 400 - cpu_usage_history[i]);
    }
    cairo_stroke(cr);

    return TRUE;
}

// Function to update CPU usage
gboolean update_cpu_usage(GtkWidget *drawing_area) {
    // Read CPU usage from /proc/stat or other sources
    FILE *stat_file = fopen("/proc/stat", "r");
    if (stat_file) {
        char line[256];
        if (fgets(line, sizeof(line), stat_file)) {
            if (strncmp(line, "cpu ", 4) == 0) {
                unsigned long user, nice, system, idle, iowait, irq, softirq;
                sscanf(line + 4, "%lu %lu %lu %lu %lu %lu %lu", &user, &nice, &system, &idle, &iowait, &irq, &softirq);
                unsigned long total = user + nice + system + idle + iowait + irq + softirq;
                double cpu_usage = 100.0 * (1.0 - ((double)idle / (double)total));

                // Store the current CPU usage in the history
                cpu_usage_history[graph_index] = cpu_usage;
                graph_index = (graph_index + 1) % NUM_DATA_POINTS;
            }
        }
        fclose(stat_file);
    }

    // Queue a redraw of the drawing area to update the graph
    gtk_widget_queue_draw(drawing_area);

    return G_SOURCE_CONTINUE;
}

int main(int argc, char *argv[]) {
    GtkWidget *window, *drawing_area;

    gtk_init(&argc, &argv);

    // Create the main application window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "CPU Usage Monitor");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 400);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a drawing area for the CPU usage graph
    drawing_area = gtk_drawing_area_new();
    gtk_widget_set_hexpand(drawing_area, TRUE);
    gtk_widget_set_vexpand(drawing_area, TRUE);
    gtk_container_add(GTK_CONTAINER(window), drawing_area);

    // Connect the draw_cpu_graph function to the "draw" signal
    g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(draw_cpu_graph), NULL);

    // Update CPU usage every second
    g_timeout_add(1000, (GSourceFunc)update_cpu_usage, drawing_area);

    // Show all widgets in the window
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
