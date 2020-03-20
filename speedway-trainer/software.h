//software definitions

//for lcd
#define lcd_rows 4
#define lcd_columns 20

//for menu scrren numbers 
#define main_menu 1
#define program_menu 2
#define backlight_menu 3
#define author_menu 4
#define wait_for_handle_menu 5
#define choose_number_of_starts_menu 6
#define training_wait_menu 7
#define training_release_menu 8
#define training_summary_single_menu 9
#define training_summary_all_menu 10

//led strip config
#define digital_led_count 8
#define reverse_digital_led_strip 1 //only 0 or 1

//time measure
#define min_timer_wait 2000
#define max_timer_wait 3000
#define single_summary_show_time 3000
void cleanUserTimes();
void addTimeToResult(byte numberOfTraining, int result);
int calculateTimeAvg();
int calculateTimeMin();
int calculateTimeMax();
