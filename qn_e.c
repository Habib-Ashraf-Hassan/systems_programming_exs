/*
Name: Ashraf Mohammed Hassan Anil
Reg No: SCT211-0255/2021
UNIT: ICS2305
*/
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

// Function to update CPU usage
gboolean update_cpu_usage(GtkWidget *label) {
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

                // Update the CPU usage label
                char usage_str[64];
                snprintf(usage_str, sizeof(usage_str), "CPU Usage: %.2f%%", cpu_usage);
                gtk_label_set_text(GTK_LABEL(label), usage_str);
            }
        }
        fclose(stat_file);
    }

    return G_SOURCE_CONTINUE;
}

int main(int argc, char *argv[]) {
    GtkWidget *window, *label, *drawing_area;

    gtk_init(&argc, &argv);

    // Create the main application window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "CPU Usage Monitor");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 400);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a label to display CPU usage
    label = gtk_label_new("CPU Usage: 0.00%");
    gtk_label_set_xalign(GTK_LABEL(label), 0.0);  // Left-align text
    gtk_label_set_yalign(GTK_LABEL(label), 0.0);  // Top-align text
    gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_LEFT);
    gtk_container_add(GTK_CONTAINER(window), label);

    // Create a drawing area for the CPU usage graph (not yet implemented)
    drawing_area = gtk_drawing_area_new();
    gtk_widget_set_hexpand(drawing_area, TRUE);
    gtk_widget_set_vexpand(drawing_area, TRUE);

    gtk_container_add(GTK_CONTAINER(window), drawing_area);

    // Update CPU usage every second
    g_timeout_add(1000, (GSourceFunc)update_cpu_usage, label);

    // Show all widgets in the window
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
