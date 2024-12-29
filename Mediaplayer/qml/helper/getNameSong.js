function getSongTitle(filePath) {
    var parts = filePath.split("/");
    var fileName = parts[parts.length - 1];
    return fileName;
}
