// to convert the output to a neat json object for data processing
var markdown_to_json = (md = "") => {
    var headers = [];
    return md.split('\n').map(a => a.trim()).filter(a => a).reduce((prev,curr) => {
        if (curr.startsWith("#")){
            var headerType = curr.split(" ")[0].length;
            var prevHeaderType = headers[headers.length - 1] ? headers[headers.length - 1].split(" ")[0].length : -1;
            if (headerType == prevHeaderType){
                headers.splice(-1) // remove last heading at this level
            } else if (headerType < prevHeaderType){
                headers.splice(headerType - prevHeaderType)
            }
            headers.push(curr)
        } else if (curr.startsWith("* ")){
            var completionLine = "* Completed "
            if (curr.startsWith(completionLine)){
                var taskName = curr.substr(completionLine.length).split(" ");
                var duration = taskName.splice(-3)[1];   
                debugger;
                taskName = taskName.join(" ");
                var objectToModify = headers.reduce((hPrev,hCurr) => hPrev[hCurr] = (hPrev[hCurr] || {}),prev)
                objectToModify[taskName] = duration;
            }
        }
        return prev;
    },{});
}