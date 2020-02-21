
// Print title on the top of OLED
void printTitle(String title, int xCursor, int yCursor) {
    u8g2.setFont(u8g2_font_crox1cb_tf);
    u8g2.setCursor(xCursor, yCursor);
    u8g2.print(title);
    u8g2.drawLine(0,12,128,12);
}

// Print main information on the center of OLED
void printInformation(String info) {
    u8g2.setFont(u8g2_font_t0_22b_tn);
    u8g2.setCursor(20, 42);
    u8g2.print(info);
}

// Print sub-information on the bottom-left of OLED
void printSubInformation(String info) {
    u8g2.setFont(u8g2_font_nine_by_five_nbp_tf);
    u8g2.setCursor(0, 60);
    u8g2.print(info);
}

// Print information unit beside the information
void printInformationUnit(String unit) {
    u8g2.setFont(u8g2_font_glasstown_nbp_tf);
    u8g2.setCursor(90, 42);
    u8g2.print(unit);
}

// Print total satellite signal on the bottom-right of OLED
void printTotalSatellite() {
    u8g2.setFont(u8g2_font_courB08_tn);
    u8g2.setCursor(105, 64);
    u8g2.print(totalSatellite, 5);
    u8g2.drawXBMP(118, 54, 10, 10, u8g2_logo_wave);
}
