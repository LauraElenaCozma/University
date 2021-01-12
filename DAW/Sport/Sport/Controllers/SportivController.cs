using Sport.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace Sport.Controllers
{
    public class SportivController : Controller
    {
        private DbCtx db = new DbCtx();
        // GET: Book
        public ActionResult Index()
        {
            /*Proba proba1 = new Proba
            {
                Denumire = "Patinaj artistic",
                Data = new System.DateTime(2018, 1, 13),
            };
            db.Probe.Add(proba1);
            db.Sportivi.Add(new Sportiv
            {
                Nume = "Moir",
                Prenume = "Scott",
                DataNasterii = new System.DateTime(1978, 4, 23),
                Tara = "Canada",
                IDProba = proba1.IDProba
            });
            db.SaveChanges();
            */
            List<Sportiv> sportivi = db.Sportivi.ToList();
            ViewBag.Sportivi = sportivi;
            return View();
        }

        /*Creati o actiune noua cu un parametru id unde view-ul afiseaza detaliile cartii care are acel numar
        drept BookId. In view-ul corespunzator actiunii ce enumera toate cartile, creati cu Razor pentru
        fiecare carte un link catre pagina cu detalii.*/

        public ActionResult Details(int? id)
        {
            if (id.HasValue)
            {
                Sportiv sportiv = db.Sportivi.Find(id);
                if (sportiv != null)
                {
                    return View(sportiv);
                }
                return HttpNotFound("Could not find the sportiv with id " + id.ToString());
            }
            return HttpNotFound("Missing id parameter!");
        }

        [HttpGet]
        public ActionResult New()
        {
            Sportiv sportiv = new Sportiv();
            sportiv.ListaProbe = getAllProbes();
            return View(sportiv);
        }

        [HttpPost]
        public ActionResult New(Sportiv sportivReq)
        {
            sportivReq.ListaProbe = getAllProbes();
            try
            {
                if (ModelState.IsValid)
                {
                    db.Sportivi.Add(sportivReq);
                    db.SaveChanges();
                    return RedirectToAction("Index");
                }
                return View(sportivReq) ;
            }
            catch (Exception e)
            {
                return View(sportivReq);
            }
        }


        [HttpGet]
        public ActionResult Edit(int? id)
        {
            if (id.HasValue)
            {
                Sportiv sportiv = db.Sportivi.Find(id);
                if (sportiv != null)
                {
                    sportiv.ListaProbe = getAllProbes();
                    return View(sportiv);
                }
                return HttpNotFound("Not found sportiv with id " + id.ToString());
            }
            return HttpNotFound("Missing id parameter!");
        }

        [HttpPut]
        public ActionResult Edit(int id, Sportiv sportivReq)
        {
            sportivReq.ListaProbe = getAllProbes();
            try
            {
                if (ModelState.IsValid)
                {
                    Sportiv sportiv = db.Sportivi.Find(id);
                    if (TryUpdateModel(sportiv))
                    {
                        sportiv.Nume = sportivReq.Nume;
                        sportiv.Prenume = sportivReq.Prenume;
                        sportiv.Tara = sportivReq.Tara;
                        sportiv.IDProba = sportivReq.IDProba;
                        sportiv.DataNasterii = sportivReq.DataNasterii;
                       
                        db.SaveChanges();
                        return RedirectToAction("Index");
                    }
                }
                return View(sportivReq);
            }
            catch (Exception e)
            {
                return View(sportivReq);
            }
        }

        [HttpDelete]
        public ActionResult Delete(int? id)
        {
            if (id.HasValue)
            {
                Sportiv sportiv = db.Sportivi.Find(id);
                if (sportiv != null)
                {
                    db.Sportivi.Remove(sportiv);
                    db.SaveChanges();
                    return RedirectToAction("Index");
                }
                return HttpNotFound("Not found sportiv with id " + id.ToString());
            }
            return HttpNotFound("Missing id parameter!");
        }

        [NonAction]
        private IEnumerable<SelectListItem> getAllProbes()
        {
            var selectedList = new List<SelectListItem>();
            foreach (var proba in db.Probe.ToList())
            {
                selectedList.Add(new SelectListItem
                {
                    Value = proba.IDProba.ToString(),
                    Text = proba.Denumire
                });
            }
            return selectedList;
        }
    }
}