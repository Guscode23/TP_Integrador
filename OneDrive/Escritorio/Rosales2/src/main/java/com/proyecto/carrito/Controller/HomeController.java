package com.proyecto.carrito.Controller;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;

import com.proyecto.carrito.model.Cliente;
import com.proyecto.carrito.model.DetalleOrden;
import com.proyecto.carrito.model.Producto;
import com.proyecto.carrito.model.Transaccion;
import com.proyecto.carrito.service.IUsuarioInterface;
//import com.proyecto.carrito.service.IUsuarioService;
import com.proyecto.carrito.service.ProductoService;

@Controller
@RequestMapping("/")
public class HomeController {
 
	private final Logger log=LoggerFactory.getLogger(HomeController.class);
	
	
	@Autowired
	private ProductoService productoService;
	
	@Autowired
	private IUsuarioInterface usuarioService;
	
	List<DetalleOrden> detalles=new ArrayList<DetalleOrden>();
	
	//Datos de la Transaccion/
	Transaccion transac= new Transaccion();
	
	@GetMapping("")
	public String home(Model model) {
		
		model.addAttribute("productos",productoService.findAll());
		
		return "Cliente/homeCliente";
	}
	
	
	@GetMapping("productohome/{id}")
	public String productoHome(@PathVariable Integer id,Model model) {
		
		log.info("Id producto enviado como parametro {}",id);
		Producto producto=new Producto();
		Optional<Producto> productoOptional=productoService.get(id);
		producto=productoOptional.get();
		model.addAttribute("producto",producto);
		return "Cliente/productohome";
	}
	
	@PostMapping("/cart")
	public String addCart(@RequestParam Integer id, @RequestParam Integer cantidad,Model model) {
		DetalleOrden detalleorden=new DetalleOrden();
		Producto producto=new Producto();
		double  sumaTotal=0;
		
		Optional<Producto> optionalProducto= productoService.get(id);
		log.info("Producto añadido:{}",optionalProducto.get());
		log.info("Cantidad:{}",cantidad);
		producto=optionalProducto.get();
		
		detalleorden.setCantidad(cantidad);
		detalleorden.setPrecio(producto.getPrecio());
		detalleorden.setNombre(producto.getNombre());
		detalleorden.setTotal(producto.getPrecio()*cantidad);
		detalleorden.setProducto(producto);
		
		
		//Validar que el prodcuto no se añade dos veces//
		Integer idProducto=producto.getId();
		boolean ingresado=detalles.stream().anyMatch(p->p.getProducto().getId()==idProducto);
		
		if(!ingresado) {
			detalles.add(detalleorden);
			
		}
		
		
		
        sumaTotal=detalles.stream().mapToDouble(dt->dt.getTotal()).sum();
		
		transac.setTotal(sumaTotal);
		model.addAttribute("cart",detalles);
		model.addAttribute("transac",transac);

				
		
		return "Cliente/carrito";
	}
	
	//Quitar producto del carrito//
	
	@GetMapping("/delete/cart/{id}")
	public String deleteProducto(@PathVariable Integer id,Model model) {
		
		//Lista nueva de productos//
		List<DetalleOrden> ordenNueva= new ArrayList<DetalleOrden>();
		
		for(DetalleOrden detalleOrden: detalles) {
			if(detalleOrden.getProducto().getId()!=id) {
				ordenNueva.add(detalleOrden);
			}
		}
		
		
		//Poner la nueva lista con los productos restantes
		detalles=ordenNueva;
		
		double sumaTotal=0;
		
        sumaTotal=detalles.stream().mapToDouble(dt->dt.getTotal()).sum();
		
		transac.setTotal(sumaTotal);
		model.addAttribute("cart",detalles);
		model.addAttribute("transac",transac);

		
		return "Cliente/carrito";
		
	}
	
	@GetMapping("/getCart")
	public String getCart(Model model) {
		model.addAttribute("cart",detalles);
		model.addAttribute("transac",transac);
		
		return "/Cliente/carrito";
	}
	
	@GetMapping("/order")
	public String order(Model model) {
		
		
	    Cliente usuario=usuarioService.findById(1).get();
	    
		
		model.addAttribute("cart",detalles);
		model.addAttribute("transac",transac);
		model.addAttribute("usuario",usuario);
		
		return "Cliente/resumenorden";
	}
	
	
		
}
	
	

