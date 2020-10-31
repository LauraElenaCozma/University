using Books.Models;
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace Books.Controllers
{
    public class BooksController : Controller
    {
        private DbCtx db = new DbCtx();
        // GET: Books
        public ActionResult Index()
        {
            List<Book> books = db.Books.ToList();
            ViewBag.Books = books;

            return View();
        }

        public ActionResult Details(int? id)
        {
            if(id.HasValue)
            {
                Book book = db.Books.Find(id);
                if(book != null)
                {
                    return View(book);
                }
                else
                {
                    return HttpNotFound("No book having this id");
                }
            }
            return RedirectToAction("Index");
        }

        public ActionResult New()
        {
            return View();
        }

        [HttpPost]
        public ActionResult Create(Book b)
        {
            b.Publisher = db.Publishers.FirstOrDefault(p => p.PublisherId.Equals(1));
            db.Books.Add(b);
            db.SaveChanges();
            return RedirectToAction("Index");
        }

        public ActionResult Edit(int id)
        {
            Book b = db.Books.Find(id);
            if(b == null)
            {
                return HttpNotFound("The book does not exist in the database");
            }
            return View(b);

        }

        [HttpPost]
        public ActionResult Update(Book b)
        {
            Book book = db.Books.Single(o => o.BookId == b.BookId);
            book.Title = b.Title;
            book.Author = b.Author;
            db.SaveChanges();
            return RedirectToAction("Index");
        }

        [HttpPost]
        public ActionResult Delete(int id)
        {
            Book b = db.Books.Find(id);
            if (b == null)
            {
                return HttpNotFound("The book does not exist in the database");
            }
            db.Books.Remove(b);
            db.SaveChanges();
            return RedirectToAction("Index");
        }

    }
}