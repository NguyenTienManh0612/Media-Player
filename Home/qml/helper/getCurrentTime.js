function getCurrentDateTime() {
    var now = new Date();
    // Lấy thời gian
    var hours = now.getHours().toString().padStart(2, '0');
    var minutes = now.getMinutes().toString().padStart(2, '0');
    //var seconds = now.getSeconds().toString().padStart(2, '0');
    var timeString = hours + ":" + minutes;// + ":" + seconds;

    return timeString;
}
