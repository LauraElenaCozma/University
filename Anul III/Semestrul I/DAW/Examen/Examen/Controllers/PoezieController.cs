using Examen.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace Examen.Controllers
{
    public class PoezieController : Controller
    {
        private DbCtx db = new DbCtx();
        // GET: Poezii
        public ActionResult Index()
        {
           List<Poezie> poezii = db.Poezii.Include("Volum").ToList();
            ViewBag.Poezii = poezii;
            return View();
        }


        [HttpGet]
        public ActionResult New()
        {
            Poezie poezie = new Poezie();
            poezie.ListaVolume = getAllVolumes();
            return View(poezie);
        }

        [HttpPost]
        public ActionResult New(Poezie poezieReq)
        {
            poezieReq.ListaVolume = getAllVolumes();
            try
            {
                if (ModelState.IsValid)
                {
                    db.Poezii.Add(poezieReq);
                    db.SaveChanges();
                    return RedirectToAction("Index");
                }
                return View(poezieReq);
            }
            catch (Exception e)
            {
                return View(poezieReq);
            }
        }


        [HttpGet]
        public ActionResult Edit(int? id)
        {
            if (id.HasValue)
            {
                Poezie poezie = db.Poezii.Find(id);
                if (poezie != null)
                {
                    poezie.ListaVolume = getAllVolumes();
                    return View(poezie);
                }
                return HttpNotFound("Nu s-a gasit poezie cu id-ul " + id.ToString());
            }
            return HttpNotFound("Missing id parameter!");
        }

        [HttpPut]
        public ActionResult Edit(int id, Poezie poezieReq)
        {
            poezieReq.ListaVolume = getAllVolumes();
            try
            {
                if (ModelState.IsValid)
                {
                    Poezie poezie = db.Poezii.Find(id);
                    if (TryUpdateModel(poezie))
                    {
                        poezie.Titlu = poezieReq.Titlu;
                        poezie.Autor = poezieReq.Autor;
                        poezie.NrStrofe = poezieReq.NrStrofe;
                        poezie.IdVolum = poezieReq.IdVolum;

                        db.SaveChanges();
                        return RedirectToAction("Index");
                    }
                }
                return View(poezieReq);
            }
            catch (Exception e)
            {
                return View(poezieReq);
            }
        }

        [HttpDelete]
        public ActionResult Delete(int? id)
        {
            if (id.HasValue)
            {
                Poezie poezie = db.Poezii.Find(id);
                if (poezie != null)
                {
                    db.Poezii.Remove(poezie);
                    db.SaveChanges();
                    return RedirectToAction("Index");
                }
                return HttpNotFound("Nu s-a gasit poezie cu id-ul " + id.ToString());
            }
            return HttpNotFound("Missing id parameter!");
        }

        [NonAction]
        private IEnumerable<SelectListItem> getAllVolumes()
        {
            var selectedList = new List<SelectListItem>();
            foreach (var volum in db.Volume.ToList())
            {
                selectedList.Add(new SelectListItem
                {
                    Value = volum.IdVolum.ToString(),
                    Text = volum.Denumire
                });
            }
            return selectedList;
        }

        //afiseaza poeziile unde titlul contine stringul s1
        //StringInTitlu/{s1}
    public ActionResult TitluContineString(String s1)
        {
            if(s1 != null)
            {
                List<Poezie> poezii = db.Poezii.ToList();
                List<Poezie> poeziiExtrase = new List<Poezie>();
                foreach (var poezie in poezii)
                {
                    if (poezie.Titlu.Contains(s1))
                        poeziiExtrase.Add(poezie);
                }
                return View("ListaPoezii", poeziiExtrase);
            }
            return HttpNotFound("Missing string parameter");
            
        }
        //StringInDenumire/{s1}
        public ActionResult DenumireContineString(String s1)
        {
            if (s1 != null)
            {
                List<Poezie> poezii = db.Poezii.Include("Volum").ToList();
                List<Poezie> poeziiExtrase = new List<Poezie>();
                foreach (var poezie in poezii)
                {
                    if (poezie.Volum.Denumire.Contains(s1))
                        poeziiExtrase.Add(poezie);
                }
                return View("ListaPoezii", poeziiExtrase);
            }
            return HttpNotFound("Missing string parameter");

        }


        //functie de cautare care cauta o poezie dupa titlu si denumirea volumului
        [HttpGet]
        public ActionResult CautaTitluDenumire()
        {
            TitluDenumireViewModel td = new TitluDenumireViewModel();
            return View(td);
        }

        [HttpPost]
        public ActionResult TitluDenumirePoezii(TitluDenumireViewModel td)
        {
            if (td.Titlu == null || td.Denumire == null)
                return HttpNotFound("Titlul si denumirea nu au fost introduse!");
            List<Poezie> poezii = db.Poezii.Include("Volum").ToList();
            List<Poezie> poeziiExtrase = new List<Poezie>();
            foreach (var poezie in poezii)
            {
                if (poezie.Volum.Denumire.Contains(td.Denumire) &&  poezie.Titlu.Contains(td.Titlu))
                    poeziiExtrase.Add(poezie);
            }
            return View("ListaPoezii", poeziiExtrase);
        }
    }
}