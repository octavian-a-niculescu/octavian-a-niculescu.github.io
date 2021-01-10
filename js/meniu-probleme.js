document.getElementById("listUL").addEventListener("click", function(e) {
    const tgt = e.target;
    const id = tgt.dataset.id;
    [...document.querySelectorAll("div.problema")]
    .forEach(div => div.classList.toggle("hide", !div.classList.contains(id)))
  })