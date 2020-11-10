using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using Books.Models;

namespace Books.Controllers
{
    public class BookTypesController : Controller
    {
        private DbCtx db = new DbCtx();
        // GET: BookTypes
        public ActionResult Index()
        {
            IEnumerable<BookType> bookTypes = db.BookTypes.ToList();
            return View(bookTypes);
        }

        // Create
        [HttpGet]
        public ActionResult New()
        {
            BookType b = new BookType();
            return View(b);
        }

        [HttpPost]
        public ActionResult New(BookType b)
        {
            try
            {
                if(ModelState.IsValid)
                {
                    //campurile au fost completate corespunzator
                    db.BookTypes.Add(b);
                    db.SaveChanges();
                    return RedirectToAction("Index");
                }
                return View(b);
            }
            catch(Exception e)
            {
                //apare o eroare; vrem sa ramanem pe pagina formularului
                return View(b);
            }
            
        }

        //Update
        [HttpGet]
        public ActionResult Edit(int? id)
        {
            if(id.HasValue)
            {
                BookType b = db.BookTypes.SingleOrDefault(bt => bt.BookTypeId == id);
                if(b == null)
                {
                    return HttpNotFound("The book type does not exist in the database");
                }
                return View(b);
            }
            return HttpNotFound("Missing id parameter");
        }

        [HttpPut]
        public ActionResult Edit(int id, BookType b)
        {
            try
            {
                if(ModelState.IsValid)
                {
                    BookType bFound = db.BookTypes.SingleOrDefault(bt => bt.BookTypeId.Equals(id));
                    if(bFound == null)
                    {
                        return HttpNotFound("The book type does not exist in the database");
                    }
                    if (TryUpdateModel(bFound))
                    {
                        bFound.Name = b.Name;
                        db.SaveChanges();
                    }
                    return RedirectToAction("Index");
                    
                }
                return View(b);
            }
            catch
            {
                return View(b);
            }
        }

        // Delete
        [HttpDelete]
        public ActionResult Delete(int? id)
        {
            if(id.HasValue)
            {
                BookType b = db.BookTypes.SingleOrDefault(bt => bt.BookTypeId == id);
                if (b == null)
                    return HttpNotFound("The book does not exist in the database");
                db.BookTypes.Remove(b);
                db.SaveChanges();
                return RedirectToAction("Index");
            }
            return HttpNotFound("Missing id parameter");
        }
    }
   
}