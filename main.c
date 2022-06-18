#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include <gtk/gtk.h>
#include <glib.h>

// fixme- make this work without globals

// list of Entry Buffers
GPtrArray* amounts = NULL;
GPtrArray* names = NULL;

void split_pay(GtkButton* self, gpointer _) {
    
}

void add_transaction(GtkButton* self, gpointer transactions) {
    GtkListBox* transaction_list = GTK_LIST_BOX(transactions);
    if (amounts==NULL) { // allocate it
	amounts = g_ptr_array_new_full(6, NULL);
	names = g_ptr_array_new_full(6, NULL);
    }

    if (0 == amounts->len ||
	0 < gtk_entry_buffer_get_bytes(
	    GTK_ENTRY_BUFFER(
		amounts->pdata[amounts->len-1]))) {

	GtkBox* box;

	// construct the GUI
	box = GTK_BOX( gtk_box_new(GTK_ORIENTATION_HORIZONTAL,10) );

	GtkEntry* name = GTK_ENTRY( gtk_entry_new() );
	gtk_entry_set_placeholder_text ( name, "name" );
	gtk_editable_set_max_width_chars( GTK_EDITABLE(name), 30 );

	GtkEntry* amount = GTK_ENTRY( gtk_entry_new() );
	gtk_entry_set_placeholder_text ( amount, "amount" );
	gtk_editable_set_max_width_chars( GTK_EDITABLE(amount), 6 );
	gtk_entry_set_input_purpose (amount, GTK_INPUT_PURPOSE_NUMBER);
	gtk_entry_set_input_hints(amount, GTK_INPUT_HINT_PRIVATE);
	gtk_editable_set_alignment(GTK_EDITABLE(amount), 1.);

	gtk_box_append(box, GTK_WIDGET(name));
	gtk_box_append(box, GTK_WIDGET(amount));

	// link the EntryBuffers to amounts and names
	g_ptr_array_add (amounts, gtk_entry_get_buffer(amount));
	g_ptr_array_add (names, gtk_entry_get_buffer(name));
	printf("%u\n", amounts->len);

	gtk_list_box_append(transaction_list, GTK_WIDGET(box));
    }
}

void activate(GtkApplication *app,
	      gpointer        user_data) {
    // initialize xml file into GUI
    GtkBuilder* builder = gtk_builder_new_from_file("gui4.xml");
    GtkWindow* window = GTK_WINDOW(gtk_builder_get_object(builder,
							  "window"));

    gtk_window_set_application (window, app);

    // start the show
    gtk_widget_show (GTK_WIDGET (window));
    // free the builder object
    g_object_unref (builder);
}

int main(int argc, char* argv[]) {
//    gtk_init();

    GtkApplication *app = gtk_application_new ("null.daknig.pay_split",
					       G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);

    int status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);
    return status;
}
