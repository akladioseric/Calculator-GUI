#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

GtkWidget *entry;
char current_input[256] = "";

static void on_button_clicked(GtkWidget *widget, gpointer data) {
    const char *label = gtk_button_get_label(GTK_BUTTON(widget));

    if (strcmp(label, "C") == 0) {
        // Clear
        current_input[0] = '\0';
        gtk_entry_set_text(GTK_ENTRY(entry), current_input);
    } else if (strcmp(label, "=") == 0) {
        // Evaluate the expression (very simple)
        double a = 0, b = 0;
        char op = 0;
        if (sscanf(current_input, "%lf %c %lf", &a, &op, &b) == 3) {
            double res = 0;
            switch (op) {
                case '+': res = a + b; break;
                case '-': res = a - b; break;
                case '*': res = a * b; break;
                case '^': res = pow(a, b); break;
                case '/':
                    if (b != 0) res = a / b;
                    else { strcpy(current_input, "Dumb"); gtk_entry_set_text(GTK_ENTRY(entry), current_input); return; }
                    break;
                default:
                    strcpy(current_input, "Stupid");
                    gtk_entry_set_text(GTK_ENTRY(entry), current_input);
                    return;
            }
            sprintf(current_input, "%.2f", res);
            gtk_entry_set_text(GTK_ENTRY(entry), current_input);
        } else {
            strcpy(current_input, "Idiot");
            gtk_entry_set_text(GTK_ENTRY(entry), current_input);
        }
    } else {
        // Append button text to input
        strcat(current_input, label);
        gtk_entry_set_text(GTK_ENTRY(entry), current_input);
    }
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // Main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Erics Calculator");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 400);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Vertical layout
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Entry display
    entry = gtk_entry_new();
    gtk_editable_set_editable(GTK_EDITABLE(entry), FALSE);
    gtk_box_pack_start(GTK_BOX(vbox), entry, FALSE, FALSE, 0);

    // Grid for buttons
    GtkWidget *grid = gtk_grid_new();
    gtk_box_pack_start(GTK_BOX(vbox), grid, TRUE, TRUE, 7);

    const char *buttons[] = {
        "7", "8", "9", "/",
        "4", "5", "6", "*",
        "1", "2", "3", "-",
        "0", "C", "=", "+",
        "(", ")", ".", "^",
    };

    for (int i = 0; i < 20; i++) {
        GtkWidget *btn = gtk_button_new_with_label(buttons[i]);
        g_signal_connect(btn, "clicked", G_CALLBACK(on_button_clicked), NULL);
        gtk_grid_attach(GTK_GRID(grid), btn, i % 4, i / 4, 1, 1);
    }

    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
