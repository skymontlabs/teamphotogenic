function showTasks(ws, limit, offset) {
    ws.send(1)
}

/*link controller

// move to click

const links = document.getElementsByTagName('a');
for(let i = 0; i < links.length; i++) {
  links[i].addEventListener('click', function(event) {
    console.log('lauren')
    event.preventDefault();
    get(links[i].href);

    window.history.pushState({},links[i].href,links[i].href)

    if (prfTog.checked) {
        prfTog.checked=false
    }
  }, false);
}

*/