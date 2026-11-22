const menuButton = document.querySelector(".menu-toggle");
const nav = document.querySelector(".nav");
if (menuButton && nav) {
  menuButton.addEventListener("click", () => {
    const isOpen = nav.classList.toggle("open");
    menuButton.setAttribute("aria-expanded", String(isOpen));
  });
  nav.querySelectorAll("a").forEach((link) => link.addEventListener("click", () => {
    nav.classList.remove("open");
    menuButton.setAttribute("aria-expanded", "false");
  }));
}
document.querySelectorAll("[data-copy]").forEach((button) => {
  button.addEventListener("click", async () => {
    const original = button.textContent;
    try {
      await navigator.clipboard.writeText(button.dataset.copy);
      button.textContent = "Copied!";
    } catch {
      button.textContent = "Select code";
    }
    window.setTimeout(() => { button.textContent = original; }, 1400);
  });
});
const year = document.querySelector("#year");
if (year) year.textContent = new Date().getFullYear();


const progress = document.createElement("div");
progress.className = "scroll-progress";
document.body.append(progress);
const pointerGlow = document.createElement("div");
pointerGlow.className = "pointer-glow";
document.body.append(pointerGlow);
const updateScrollProgress = () => {
  const max = document.documentElement.scrollHeight - window.innerHeight;
  progress.style.width = (max > 0 ? Math.min(100, window.scrollY / max * 100) : 0) + "%";
};
window.addEventListener("scroll", updateScrollProgress, { passive: true });
updateScrollProgress();
if (window.matchMedia("(pointer:fine)").matches) {
  window.addEventListener("pointermove", (event) => {
    pointerGlow.style.left = event.clientX + "px";
    pointerGlow.style.top = event.clientY + "px";
  }, { passive: true });
}
const revealTargets = document.querySelectorAll(".section-heading,.feature-card,.architecture-panel,.instruction-row,.code-card,.eco-card,.terminal-card,.closing");
revealTargets.forEach((element, index) => {
  element.classList.add("reveal");
  element.style.setProperty("--i", index % 6);
});
if ("IntersectionObserver" in window) {
  const revealObserver = new IntersectionObserver((entries) => {
    entries.forEach((entry) => {
    if (entry.isIntersecting) {
      entry.target.classList.add("visible");
      revealObserver.unobserve(entry.target);
    }
    });
  }, { threshold: 0.12, rootMargin: "0px 0px -35px 0px" });
  revealTargets.forEach((element) => revealObserver.observe(element));
} else revealTargets.forEach(element => element.classList.add("visible"));
document.querySelectorAll(".feature-card,.eco-card").forEach(card => {
  card.addEventListener("pointermove", (event) => {
    const rect = card.getBoundingClientRect();
    card.style.setProperty("--mx", (event.clientX - rect.left) + "px");
    card.style.setProperty("--my", (event.clientY - rect.top) + "px");
  });
});

document.querySelectorAll(".filter-btn").forEach(button=>button.addEventListener("click",()=>{
 const filter=button.dataset.filter;
 document.querySelectorAll(".filter-btn").forEach(item=>item.classList.toggle("active",item===button));
 document.querySelectorAll(".example-card").forEach(card=>card.hidden=filter!=="all"&&card.dataset.category!==filter);
}));
const exampleSearch=document.querySelector("#example-search");
if(exampleSearch) exampleSearch.addEventListener("input",()=>{
 const term=exampleSearch.value.toLowerCase();
 document.querySelectorAll(".example-card").forEach(card=>card.hidden=!card.textContent.toLowerCase().includes(term));
});
const editor=document.querySelector("#playground-code");
const output=document.querySelector("#playground-output");
const runButton=document.querySelector("#playground-run");
const resetButton=document.querySelector("#playground-reset");
const copyEditor=document.querySelector("#playground-copy");
const initialCode=editor?editor.value:"";
if(runButton&&editor&&output)runButton.addEventListener("click",()=>{
 output.textContent="This browser playground is a syntax preview, not a ByteC VM.\n\nYour code is ready to copy into a .bytec file and run with the installed ByteC interpreter.";
});
if(resetButton&&editor&&output)resetButton.addEventListener("click",()=>{editor.value=initialCode;output.textContent="Editor restored to the example.";});
if(copyEditor&&editor)copyEditor.addEventListener("click",async()=>{try{await navigator.clipboard.writeText(editor.value);copyEditor.textContent="Copied";setTimeout(()=>copyEditor.textContent="Copy code",1200)}catch{copyEditor.textContent="Copy unavailable"}});
