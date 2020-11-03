using Books.Models;
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace Books.ViewModels
{
    public class BookAndBookTypesViewModel
    {
        //[Required]
        public Book Book { get; set; }
        //[Required]
        public IEnumerable<BookType> BookTypes { get; set; }
    }
}