document.querySelectorAll(".fa-arrow-custom").forEach(elem => {
  elem.addEventListener("click", function() {
    document.querySelector(".executie-problema").classList.toggle("hide");
    document.querySelector(".executie2-problema").classList.toggle("hide");
  })
});