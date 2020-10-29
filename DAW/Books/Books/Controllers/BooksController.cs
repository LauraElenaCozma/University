using Books.Models;
using System;
using System.Collections.Generic;
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

    }
}