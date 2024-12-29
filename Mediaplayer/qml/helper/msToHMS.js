function msToHMS(ms) {
    // 1- Convert to seconds:
    var seconds = ms / 1000;

    // 2- Extract hours:
    var hours = parseInt(seconds / 3600); // 3600 seconds in 1 hour
    seconds = parseInt(seconds % 3600); // extract the remaining seconds after extracting hours

    // 3- Extract minutes:
    var minutes = parseInt(seconds / 60); // 60 seconds in 1 minute

    // 4- Keep only seconds not extracted to minutes:
    seconds = parseInt(seconds % 60);

    // 5 - Format so it shows a leading zero if needed
    let hoursStr = ("00" + hours).slice(-2);
    let minutesStr = ("00" + minutes).slice(-2);
    let secondsStr = ("00" + seconds).slice(-2);

    if (hours !== 0) {
        return(hoursStr + ":" + minutesStr + ":" + secondsStr);
    } else {
        return(minutesStr + ":" + secondsStr);
    }
}
