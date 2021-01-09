using Books_CRUD.Models;
using Books_CRUD.Models.Database;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace Books_CRUD.Controllers
{
    public class BookController : Controller
    {
        private DbCtx db = new DbCtx();
        // GET: Book
        public ActionResult Index()
        {
            List<Book> books = db.Books.ToList();
            return View(books);
        }

        /*Creati o actiune noua cu un parametru id unde view-ul afiseaza detaliile cartii care are acel numar
        drept BookId. In view-ul corespunzator actiunii ce enumera toate cartile, creati cu Razor pentru
        fiecare carte un link catre pagina cu detalii.*/

        public ActionResult Details(int? id)
        {
            if(id.HasValue)
            {
                Book book = db.Books.Find(id);
                if(book != null)
                {
                    return View(book);
                }
                return HttpNotFound("Could not find the book with id " + id.ToString());
            }
            return HttpNotFound("Missing id parameter!");
        }

        [HttpGet]
        public ActionResult New()
        {
            Book book = new Book();
            return View(book);
        }

        [HttpPost]
        public ActionResult New(Book bookReq)
        {
            try
            {
                if(ModelState.IsValid)
                {
                    db.Books.Add(bookReq);
                    db.SaveChanges();
                    return RedirectToAction("Index");
                }
                return View(bookReq);
            }
            catch(Exception e)
            {
                return View(bookReq);
            }
        }
        

        [HttpGet]
        public ActionResult Edit(int? id)
        {
            if(id.HasValue)
            {
                Book book = db.Books.Find(id);
                if(book != null)
                {
                    return View(book);
                }
                return HttpNotFound("Not found book with id " + id.ToString());
            }
            return HttpNotFound("Missing id parameter!");
        }

        [HttpPut]
        public ActionResult Edit(int id, Book bookReq)
        {
            try
            {
                if(ModelState.IsValid)
                {
                    Book book = db.Books.Find(id);
                    if(TryUpdateModel(book))
                    {
                        book.Title = bookReq.Title;
                        book.Author = bookReq.Author;
                        book.Summary = bookReq.Summary;
                        db.SaveChanges();
                        return RedirectToAction("Index");
                    }
                }
                return View(bookReq);
            }
            catch(Exception e)
            {
                return View(bookReq);
            }
        }

        [HttpDelete]
        public ActionResult Delete(int? id)
        {
            if (id.HasValue)
            {
                Book book = db.Books.Find(id);
                if (book != null)
                {
                    db.Books.Remove(book);
                    db.SaveChanges();
                    return RedirectToAction("Index");
                }
                return HttpNotFound("Not found book with id " + id.ToString());
            }
            return HttpNotFound("Missing id parameter!");
        }
    }
}