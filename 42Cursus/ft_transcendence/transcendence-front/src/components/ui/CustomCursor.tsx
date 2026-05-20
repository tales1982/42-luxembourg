import { useEffect, useRef } from "react";

export function CustomCursor() {
  const cursorRef = useRef<HTMLDivElement>(null);
  const trailRef = useRef<HTMLDivElement>(null);

  useEffect(() => {
    const cursorEl = cursorRef.current;
    const trailEl = trailRef.current;
    if (!cursorEl || !trailEl) return;

    const coarsePointer = window.matchMedia("(hover: none) and (pointer: coarse)");
    if (coarsePointer.matches) return;

    let targetX = -100;
    let targetY = -100;
    let trailX = -100;
    let trailY = -100;
    let rafId = 0;

    const update = () => {
      const dx = targetX - trailX;
      const dy = targetY - trailY;
      trailX += dx * 0.2;
      trailY += dy * 0.2;

      cursorEl.style.left = `${targetX}px`;
      cursorEl.style.top = `${targetY}px`;
      trailEl.style.left = `${trailX}px`;
      trailEl.style.top = `${trailY}px`;

      rafId = requestAnimationFrame(update);
    };

    const onMove = (e: MouseEvent) => {
      targetX = e.clientX;
      targetY = e.clientY;
    };

    const onLeave = () => {
      cursorEl.style.opacity = "0";
      trailEl.style.opacity = "0";
    };

    const onEnter = () => {
      cursorEl.style.opacity = "1";
      trailEl.style.opacity = "0.5";
    };

    window.addEventListener("mousemove", onMove, { passive: true });
    window.addEventListener("mouseout", onLeave);
    window.addEventListener("mouseover", onEnter);

    rafId = requestAnimationFrame(update);

    return () => {
      window.removeEventListener("mousemove", onMove);
      window.removeEventListener("mouseout", onLeave);
      window.removeEventListener("mouseover", onEnter);
      cancelAnimationFrame(rafId);
    };
  }, []);

  return (
    <>
      <div className="custom-cursor" ref={cursorRef} />
      <div className="custom-cursor-trail" ref={trailRef} />
    </>
  );
}
