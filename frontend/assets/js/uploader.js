function preventDefaults (e) {
  e.preventDefault()
  e.stopPropagation()
}

function highlight(e) {
  dropArea.classList.add('highlight')
}

function unhighlight(e) {
  dropArea.classList.remove('highlight')
}

function handleDrop(e) {
  let dt = e.dataTransfer
  let files = dt.files
  alert(files)

  handleFiles(files)
}



function uploadFile(file) {
  var url = 'YOUR URL HERE'
  var xhr = new XMLHttpRequest()
  var formData = new FormData()
  xhr.open('POST', url, true)

  xhr.addEventListener('readystatechange', function(e) {
    if (xhr.readyState == 4 && xhr.status == 200) {
      // Done. Inform the user
    }
    else if (xhr.readyState == 4 && xhr.status != 200) {
      // Error. Inform the user
    }
  })

  formData.append('file', file)
  xhr.send(formData)
}


function previewFile(file) {
  let reader = new FileReader()
  reader.readAsDataURL(file)
  reader.onloadend = function() {
    let img = document.createElement('img')
    img.src = reader.result
    img.className='pointer'
    upgal.appendChild(img)

    prvIm.src=reader.result
    Upd.className=''
    dropArea.className='A y z'
  }
}





function handleFiles(files) {
  files = [...files]
  files.forEach(uploadFile)
  files.forEach(previewFile)
  Upd.className=''
  ptxt.className='dn'
}