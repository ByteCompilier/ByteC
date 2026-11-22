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
    const container = button.closest(".code-block, .example-card");
    const code = container ? container.querySelector("pre") : null;
    const value = code ? code.textContent.replace(/\\r\\n/g, "\\n").replace(/\\n+$/g, "") : button.dataset.copy || "";
    try {
      if (navigator.clipboard && window.isSecureContext) {
        await navigator.clipboard.writeText(value);
      } else {
        const helper = document.createElement("textarea");
        helper.value = value;
        helper.style.position = "fixed";
        helper.style.opacity = "0";
        document.body.append(helper);
        helper.select();
        const copied = document.execCommand("copy");
        helper.remove();
        if (!copied) throw new Error("Copy failed");
      }
      button.textContent = "Copied!";
    } catch {
      button.textContent = "Copy unavailable";
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
const revealTargets = document.querySelectorAll(".section-heading,.feature-card,.architecture-panel,.instruction-row,.code-card,.eco-card,.terminal-card,.closing,.doc-section,.example-card,.page-card,.section");
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

const filterButtons = document.querySelectorAll(".filter-btn");
const exampleCards = document.querySelectorAll(".example-card");
const exampleSearch = document.querySelector("#example-search");
let activeExampleFilter = "all";
let activeExampleSearch = "";
const applyExampleFilters = () => {
  exampleCards.forEach(card => {
    const matchesFilter = activeExampleFilter === "all" || card.dataset.category === activeExampleFilter;
    const matchesSearch = card.textContent.toLowerCase().includes(activeExampleSearch);
    card.hidden = !(matchesFilter && matchesSearch);
  });
};
filterButtons.forEach(button => button.addEventListener("click", () => {
  activeExampleFilter = button.dataset.filter || "all";
  filterButtons.forEach(item => item.classList.toggle("active", item === button));
  applyExampleFilters();
}));
if (exampleSearch) exampleSearch.addEventListener("input", () => {
  activeExampleSearch = exampleSearch.value.toLowerCase().trim();
  applyExampleFilters();
});


