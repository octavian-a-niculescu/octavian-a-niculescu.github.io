let classCounter = 1;
let pasiExecutie = document.querySelectorAll(".pas-executie");

document.querySelector(".fa-arrow-right").addEventListener("click", function() {
    if(classCounter < 5)
    {
        ++classCounter;
        document.querySelector(".pas" + classCounter.toString()).classList.toggle("hide");
    }  
});

document.querySelector(".fa-arrow-left").addEventListener("click", function() {
    if(classCounter > 1)
    {
        document.querySelector(".pas" + classCounter.toString()).classList.toggle("hide");
        --classCounter;
    }  
});