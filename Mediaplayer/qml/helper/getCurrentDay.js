function getCurrentDate() {
    var now = new Date();

    //var dayOfWeek = daysOfWeek[now.getDay()];
    var month = now.getMonth() + 1;
    var day = now.getDate();
    //var year = now.getFullYear();

    var dateString = day + "." + month;

    return dateString;
}
