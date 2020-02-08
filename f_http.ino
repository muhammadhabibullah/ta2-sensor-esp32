
String generateGetHTTP(String url) {
    
    String request = String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + String(SERVER_HOST) + "\r\n" + 
                 "Connection: close\r\n\r\n";
    return request;
    
}
